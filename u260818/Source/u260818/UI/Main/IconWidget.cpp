// Fill out your copyright notice in the Description page of Project Settings.


#include "IconWidget.h"
#include "IconDragDropOperation.h"
#include "SlotWidget.h"
#include "../../Subsystem/UISubsystem.h"
#include "InventoryWidget.h"
#include "../../Player/InventoryComponent.h"


UIconWidget::UIconWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UIconWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

FReply UIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		switch (mParentSlot->GetSlotType())
		{
		case ESlotType::Inventory:
			UseInventoryItem();
			break;
		case ESlotType::Skill:
			UseSkill();
			break;
		case ESlotType::Quick:
			UseQuickSlotItem();
		}
	}
	else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// Drag 시작 이벤트를 발생시킨다.
		FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(
			InMouseEvent, this, EKeys::LeftMouseButton);

		return EventReply.NativeReply;
	}
	
	// Handled()로 처리를 하여 이 위젯이 마우스 클릭 이벤트를 처리했다는 의미가 된다.
	return FReply::Unhandled();
}

FReply UIconWidget::NativeOnMouseMove(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

void UIconWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// Drag를 하기 위한 Operation을 생성한다.
	UIconDragDropOperation* DragIcon = NewObject<UIconDragDropOperation>();

	DragIcon->mDragIcon = this;
	DragIcon->mDragStartSlot = mParentSlot;
	DragIcon->Pivot = EDragPivot::MouseDown;

	// Drag할 때 보여줄 Icon을 새로 생성하여 보여주게 한다.
	UIconWidget* DragRenderWidget = CreateWidget<UIconWidget>(GetWorld(),
		mDragIconClass);

	DragRenderWidget->mIconImage->SetBrushFromTexture(mIconTexture);
	// Alpha를 0.5로 주어서 반투명하게 출력되도록 한다.
	DragRenderWidget->mIconImage->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.5f));
	DragRenderWidget->EnableCount(false);

	DragIcon->DefaultDragVisual = DragRenderWidget;

	OutOperation = DragIcon;
}

void UIconWidget::SetIconImage(UTexture2D* Image)
{
	mIconTexture = Image;
	mIconImage->SetBrushFromTexture(Image);
}

void UIconWidget::SetCount(int32 Count)
{
	mCountText->SetText(FText::FromString(FString::FromInt(Count)));
}

void UIconWidget::EnableCount(bool Enable)
{
	if (Enable)
		mCountText->SetVisibility(ESlateVisibility::Visible);
	else
		mCountText->SetVisibility(ESlateVisibility::Collapsed);
}

void UIconWidget::UseInventoryItem()
{
	UUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (UISubsystem)
	{
		UInventoryWidget* InventoryWidget = UISubsystem->FindWidget<UInventoryWidget>(TEXT("Inventory"));

		if (InventoryWidget)
		{
			InventoryWidget->GetInventoryComponent()->UseItem(mParentSlot->GetIndex());
		}
	}
}

void UIconWidget::UseSkill()
{
}

void UIconWidget::UseQuickSlotItem()
{
}

