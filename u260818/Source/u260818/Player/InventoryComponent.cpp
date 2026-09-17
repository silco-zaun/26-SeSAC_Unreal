// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Item/ItemObject.h"
#include "../Subsystem/AssetSubsystem.h"
#include "../Subsystem/UISubsystem.h"
#include "../UI/Main/InventoryWidget.h"
#include "MainPlayerState.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(Sac8Debug, Warning, TEXT("InventoryComponent BeginPlay"));

	UAssetSubsystem* AssetSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSubsystem)
	{
		// 에셋매니저에 아이템정보가 로딩이 완료되었는지 판단한다.
		if (AssetSubsystem->GetLoadItemInfo())
		{
			ItemInfoLoadComplete();
		}
		else
		{
			AssetSubsystem->AddItemDataAssetLoadingDelegate<UInventoryComponent>(this,
				&UInventoryComponent::ItemInfoLoadComplete);
		}
	}
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	mItemList.Init(nullptr, 30);
}

bool UInventoryComponent::AddItem(const FItemTableInfo& ItemInfo)
{
	int32 MaxCount = mItemList.Num();

	if (mItemCount == MaxCount)
		return false;

	if (ItemInfo.UILayerType == EItemUILayerType::Layered)
	{
		UItemObject* Item = nullptr;

		for (int32 i = 0; i < MaxCount; ++i)
		{
			if (mItemList[i])
			{
				if (mItemList[i]->GetItemInfo().ItemName ==
					ItemInfo.ItemName)
				{
					Item = mItemList[i];
					Item->AddItemCount();

					// 카운트 벼노하가 생길경우 등록된 함수 호출.
					if (mItemCountChangeDelegate.IsBound())
						mItemCountChangeDelegate.Broadcast(mItemList[i]->GetItemCount(), i);
					break;
				}
			}
		}

		// 동일한 아이템이 없을 경우
		if (!Item)
		{
			Item = NewObject<UItemObject>();
			Item->SetItemInfo(ItemInfo);

			// 인벤토리 칸에서 비어있는 칸을 찾는다.
			for (int32 i = 0; i < MaxCount; ++i)
			{
				if (!mItemList[i])
				{
					mItemList[i] = Item;
					++mItemCount;

					if (mItemChangeDelegate.IsBound())
						mItemChangeDelegate.Broadcast(mItemList[i], i);

					break;
				}
			}
		}
	}
	else
	{
		UItemObject* Item = NewObject<UItemObject>();
		Item->SetItemInfo(ItemInfo);

		// 인벤토리 칸에서 비어있는 칸을 찾는다.
		for (int32 i = 0; i < MaxCount; ++i)
		{
			if (!mItemList[i])
			{
				mItemList[i] = Item;
				++mItemCount;

				if (mItemChangeDelegate.IsBound())
					mItemChangeDelegate.Broadcast(mItemList[i], i);

				break;
			}
		}
	}

	return true;
}

void UInventoryComponent::SwapItem(int32 StartIndex, int32 EndIndex)
{
	mItemList.Swap(StartIndex, EndIndex);

	if (mItemChangeDelegate.IsBound())
	{
		mItemChangeDelegate.Broadcast(mItemList[StartIndex], StartIndex);
		mItemChangeDelegate.Broadcast(mItemList[EndIndex], EndIndex);
	}
}

bool UInventoryComponent::UseItem(int32 Index)
{
	if (Index < 0 || Index >= mItemList.Num())
		return false;
	else if (!IsValid(mItemList[Index]))
		return false;

	switch (mItemList[Index]->GetItemInfo().Type)
	{
	case EItemType::Weapon:
		UseWeapon(Index);
		break;
	case EItemType::Armor:
		UseArmor(Index);
		break;
	case EItemType::Potion:
		UsePotion(Index);
		break;
	}

	return true;
}

void UInventoryComponent::ItemInfoLoadComplete()
{
	// 아이템을 가지고 있다면 가지고 있는 아이템을 위젯에 보여준다.
	// 단, 지금은 없으니 임시로 아이템을 몇개 생성해서 추가해본다.
	UAssetSubsystem* AssetSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (!AssetSubsystem)
		return;

	TArray<FName> ItemNames;

	ItemNames.Add(TEXT("Sword_001"));
	ItemNames.Add(TEXT("Armor_001"));
	ItemNames.Add(TEXT("HPPotionS"));

	for (int32 i = 0; i < 10; ++i)
	{
		const FItemTableInfo* ItemInfo = AssetSubsystem->FindItemInfo(ItemNames[FMath::RandRange(0, 2)]);

		if (!ItemInfo)
			continue;

		AddItem(*ItemInfo);
	}

	// 인벤토리 위젯 초기화
	UUISubsystem* UISubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (UISubsystem)
	{
		// 인벤토리 위젯을 얻어온다.
		UInventoryWidget* Inventory = UISubsystem->FindWidget<UInventoryWidget>(TEXT("Inventory"));

		if (Inventory)
		{
			Inventory->InitInventory(this);
		}
	}
}

void UInventoryComponent::UsePotion(int32 Index)
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!OwnerCharacter)
		return;

	AMainPlayerState* State = OwnerCharacter->GetPlayerState<AMainPlayerState>();

	if (!State)
		return;

	const FItemTableInfo& ItemInfo = mItemList[Index]->GetItemInfo();

	for (auto Option : ItemInfo.Options)
	{
		switch (Option.Type)
		{
		case EItemOptionType::Attack:
			break;
		case EItemOptionType::Defense:
			break;
		case EItemOptionType::HPMax:
			break;
		case EItemOptionType::MPMax:
			break;
		case EItemOptionType::HPRecovery:
			State->AddHP(Option.Option);
			break;
		case EItemOptionType::MPRecovery:
			break;
		case EItemOptionType::MoveSpeed:
			break;
		case EItemOptionType::AttackSpeed:
			break;
		case EItemOptionType::AttackDistance:
			break;
		case EItemOptionType::CriticalRatio:
			break;
		case EItemOptionType::CriticalDamage:
			break;
		default:
			break;
		}
	}

	mItemList[Index]->AddItemCount(-1);
	if (mItemList[Index]->GetItemCount() == 0)
	{
		mItemList[Index] = nullptr;

		if (mItemChangeDelegate.IsBound())
			mItemChangeDelegate.Broadcast(mItemList[Index], Index);
	}
	else
	{
		if (mItemCountChangeDelegate.IsBound())
			mItemCountChangeDelegate.Broadcast(mItemList[Index]->GetItemCount(), Index);
	}
}

void UInventoryComponent::UseWeapon(int32 Index)
{
}

void UInventoryComponent::UseArmor(int32 Index)
{
}
