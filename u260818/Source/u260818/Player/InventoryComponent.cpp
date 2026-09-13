// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Item/ItemObject.h"

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

	// ...
	
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

				break;
			}
		}
	}


	return true;
}

