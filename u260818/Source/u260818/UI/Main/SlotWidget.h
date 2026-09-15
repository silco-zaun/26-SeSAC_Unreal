// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USlotWidget(const FObjectInitializer& ObjectInitializer);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UIconWidget> mIcon;

	uint32 mIndex = 0;

	ESlotType mSlotType = ESlotType::Inventory;

public:
	void SetSlotIndex(uint32 Index)
	{
		mIndex = Index;
	}

	void SetSlotType(ESlotType Type)
	{
		mSlotType = Type;
	}

public:
	ESlotType GetSlotType() const
	{
		return mSlotType;
	}

	uint32 GetIndex() const
	{
		return mIndex;
	}

protected:
	virtual void NativeOnInitialized();
	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	void SetItem(class UItemObject* Item);
	void SetItemCount(int32 Count);
};
