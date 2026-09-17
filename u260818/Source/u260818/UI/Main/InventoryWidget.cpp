// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "SlotWidget.h"
#include "../../Player/InventoryComponent.h"


UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 위젯 블루프린트에서 변수여부 체크가 안되어 있을 경우 GetWidgetFromName 함수를
	// 이용하여 배치된 위젯이 객체를 얻어올 수 있다.
	mTitleBar = Cast<UBorder>(GetWidgetFromName(TEXT("TitleBar")));

	mCloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::CloseButtonClick);

	UE_LOG(Sac8Debug, Warning, TEXT("Inventory Init"));
}

FReply UInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	// 마우스 왼쪽버튼을 누른게 아닐 경우
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
		return FReply::Unhandled();

	// 마우스 위치가 TitleBar 안이 아니라면 동작하지 않는다.
	// GetScreenSpacePosition : 화면에서의 마우스 위치를 얻어온다.
	if (!mTitleBar->GetCachedGeometry().IsUnderLocation(
		InMouseEvent.GetScreenSpacePosition()))
		return FReply::Unhandled();

	mDragEnable = true;

	mDragStartMousePos = InMouseEvent.GetScreenSpacePosition();

	// GetRenderTranform : 출력할 Transform 정보.
	mDragStartWidgetPos = GetRenderTransform().Translation;

	// Handled()로 처리를 하여 이 위젯이 마우스 클릭 이벤트를 처리했다는 의미가 된다.
	// CaptureMouse 함수로 TakeWidget을 지정하면 마우스를 누른 뒤부터는 마우스 커서가
	// 위젯 밖으로 나가도 이 위젯이 계속 마우스 이벤트를 받게 된다.
	return FReply::Handled().CaptureMouse(TakeWidget());
}

FReply UInventoryWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	// 마우스 왼쪽버튼을 누른게 아닐 경우
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
		return FReply::Unhandled();

	mDragEnable = false;

	// Mouse Capture를 해제한다.
	return FReply::Handled().ReleaseMouseCapture();
}

FReply UInventoryWidget::NativeOnMouseMove(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	if (!mDragEnable)
		return FReply::Unhandled();

	// 현재 마우스 위치를 얻어온다.
	FVector2D CurrentMousePos = InMouseEvent.GetScreenSpacePosition();

	// Drag를 시작한 위치와 비교하여 얼마나 떨어졌는지 구한다.
	FVector2D MouseDelta = CurrentMousePos - mDragStartMousePos;

	// DPI Scale을 얻어온다.
	float ViewScale = UWidgetLayoutLibrary::GetViewportScale(this);

	// 마우스가 이동한 양을 ViewScale을 이용하여 화면에서 움직인 양으로 변경한다.
	FVector2D WidgetPos = mDragStartWidgetPos + MouseDelta / ViewScale;

	SetRenderTranslation(WidgetPos);

	return FReply::Handled();
}

// Component를 넘겨야 하나?
// Inventory Max Count, Item Object를 넘기는건?
void UInventoryWidget::InitInventory(UInventoryComponent* Inventory)
{
	mInventoryComponent = Inventory;

	int32 MaxCount = mInventoryComponent->GetInventoryMaxCount();

	for (int32 i = 0; i < MaxCount; ++i)
	{
		FString SlotName = FString::Printf(TEXT("WB_Slot_%03d"), i + 1);

		USlotWidget* SlotWidget = Cast<USlotWidget>(GetWidgetFromName(*SlotName));

		SlotWidget->SetSlotIndex(i);
		SlotWidget->SetItem(nullptr);

		mSlotWidgetArray.Add(SlotWidget);

		UItemObject* Item = mInventoryComponent->GetItem(i);

		if (Item)
			SlotWidget->SetItem(Item);
	}

	mInventoryComponent->AddItemChangeCallback<UInventoryWidget>(this,
		&UInventoryWidget::ItemChange);
	mInventoryComponent->AddItemCountChangeCallback<UInventoryWidget>(this,
		&UInventoryWidget::ItemCountChange);
}

void UInventoryWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryWidget::ItemChange(UItemObject* Item, int32 Index)
{
	mSlotWidgetArray[Index]->SetItem(Item);
}

void UInventoryWidget::ItemCountChange(int32 Count, int32 Index)
{
	mSlotWidgetArray[Index]->SetItemCount(Count);
}
