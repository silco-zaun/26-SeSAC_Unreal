// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UItemInfoWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>	mItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage>	mItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>	mItemLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>	mItemDesc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>	mItemPrice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>	mItemSell;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UListView>	mOptionList;

public:
	void SetItemInfo(const FItemTableInfo& Info, int32 Upgrade);

protected:
	virtual void NativeOnInitialized();
};
