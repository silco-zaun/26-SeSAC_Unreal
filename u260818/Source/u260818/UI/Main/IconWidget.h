// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "IconWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UIconWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UIconWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWIdget))
	TObjectPtr<UImage> mIconImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mCountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UIconWidget> mDragIconClass;

	class USlotWidget* mParentSlot = nullptr;
	UTexture2D* mIconTexture = nullptr;

	bool mMouseOn = false;

public:
	void SetParentSlot(class USlotWidget* ParentSlot)
	{
		mParentSlot = ParentSlot;
	}

protected:
	virtual void NativeOnInitialized();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

public:
	void SetIconImage(UTexture2D* Image);
	void SetCount(int32 Count);
	void EnableCount(bool Enable);

private:
	void UseInventoryItem();
	void UseSkill();
	void UseQuickSlotItem();
	void InventoryItemRender();
	void QuickSlotItemRender();
	void SkillInfoRender();
};
