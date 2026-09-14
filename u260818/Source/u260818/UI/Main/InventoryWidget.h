// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	// 위젯 블루프린트에서 배치한 위젯이 변수여부 체크가 되어있을 경우
	// UPROPERTY의 meta에 BindWidget을 이용해서 배치한 위젯의 객체를
	// 얻어올 수 있다. 변수 이름은 반드시 위젯 블루프린트에서 작성한 이름과
	// 동일해야 한다.
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> mCloseButton;

	UPROPERTY(VIsibleAnywhere)
	TObjectPtr<UBorder> mTitleBar;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class USlotWidget>> mSlotWidgetArray;

	TObjectPtr<class UInventoryComponent> mInventoryComponent;

	bool mDragEnable = false;

	// Drag를 시작한 마우스 위치.
	FVector2D mDragStartMousePos;

	// Drag를 시작했을 때 위젯의 위치.
	FVector2D mDragStartWidgetPos;

public:
	class UInventoryComponent* GetInventoryComponent()
	{
		return mInventoryComponent;
	}

protected:
	virtual void NativeOnInitialized();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	void InitInventory(class UInventoryComponent* Inventory);

private:
	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void ItemChange(class UItemObject* Item, int32 Index);

	UFUNCTION()
	void ItemCountChange(int32 Count, int32 Index);
};
