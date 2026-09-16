// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "ItemInfoWidget.h"
#include "../../Item/ItemObject.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainWidget::EnableItemInfoWidget(bool Enable)
{
	if (Enable)
		mItemInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else
		mItemInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::ComputeItemInfoLocation(const FPointerEvent& InMouseEvent)
{
	// ItemInfoWidget의 CanvasPanelSlot을 구한다.
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(mItemInfo->Slot);

	// ScreenSpace에서의 마우스 위치를 구한다.
	FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();

	// ItemInfoWidget의 부모 Panel을 구한다.
	UPanelWidget* ParentPanel = mItemInfo->GetParent();

	// 마우스 위치를 이 위젯 내부에서의 위치로 구한다.
	FVector2D WidgetPos = ParentPanel->GetCachedGeometry().AbsoluteToLocal(MousePos);

	// 정확하게 마우스의 위치로 나오기 때문에 이 위치에서 오른쪽으로
	// 약간 떨어지게 좌표를 지정한다.
	WidgetPos.X += 20.0;

	PanelSlot->SetPosition(WidgetPos);
}

void UMainWidget::SetItemInfo(UItemObject* Item)
{
	mItemInfo->SetItemInfo(Item->GetItemInfo(),
		Item->GetItemUpgrade());
}
