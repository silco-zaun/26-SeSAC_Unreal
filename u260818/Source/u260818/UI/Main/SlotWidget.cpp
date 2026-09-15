// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "IconWidget.h"
#include "../../Item/ItemObject.h"
#include "IconDragDropOperation.h"
#include "InventoryWidget.h"
#include "../../Subsystem/UISubsystem.h"
#include "../../Player/InventoryComponent.h"


USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void USlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mIcon->SetParentSlot(this);
}

bool USlotWidget::NativeOnDrop(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIconDragDropOperation* DragIcon = Cast<UIconDragDropOperation>(InOperation);

	if (!DragIcon)
		return false;
	else if (DragIcon->mDragStartSlot->mIndex == mIndex)
		return false;

	UUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (!UISubsystem)
		return false;

	UInventoryWidget* Inventory = UISubsystem->FindWidget<UInventoryWidget>(TEXT("Inventory"));

	if (!Inventory)
		return false;

	// 인벤토리 컴포넌트를 얻어온다.
	UInventoryComponent* InventoryComponent = Inventory->GetInventoryComponent();

	if (!InventoryComponent)
		return false;

	InventoryComponent->SwapItem(DragIcon->mDragStartSlot->mIndex,
		mIndex);

	return true;

}

void USlotWidget::SetItem(UItemObject* Item)
{
	if (Item)
	{
		mIcon->SetIconImage(Item->GetItemInfo().IconImage);
		mIcon->SetVisibility(ESlateVisibility::Visible);

		if (Item->GetItemInfo().UILayerType == EItemUILayerType::Layered)
		{
			mIcon->EnableCount(true);
			mIcon->SetCount(Item->GetItemCount());
		}
		else
		{
			mIcon->EnableCount(false);
		}
	}
	else
	{
		mIcon->SetIconImage(nullptr);
		mIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USlotWidget::SetItemCount(int32 Count)
{
	mIcon->SetCount(Count);
}
