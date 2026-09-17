// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWidget.h"
#include "ItemOptionEntryObject.h"



UItemInfoWidget::UItemInfoWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{

}

void UItemInfoWidget::SetItemInfo(const FItemTableInfo& Info,
	int32 Upgrade)
{
	FString ItemName = Info.ItemName + FString::Printf(TEXT(" + %d"), Upgrade);

	mItemName->SetText(FText::FromString(ItemName));

	mItemIcon->SetBrushFromTexture(Info.IconImage);

	FString ItemLevel = FString::Printf(TEXT("Level : %d"), Info.Level);

	mItemLevel->SetText(FText::FromString(ItemLevel));

	mItemDesc->SetText(FText::FromString(Info.Desc));

	FString Price = FString::Printf(TEXT("구매가격 : %d"), Info.PurchasePrice);

	mItemPrice->SetText(FText::FromString(Price));

	FString Sell = FString::Printf(TEXT("판매가격 : %d"), Info.SellPrice);

	mItemSell->SetText(FText::FromString(Sell));

	// 옵션 목록을 비워준다.
	mOptionList->ClearListItems();

	// 옵션 수만큼 반복한다.
	for (auto Option : Info.Options)
	{
		UItemOptionEntryObject* EntryObject =
			NewObject<UItemOptionEntryObject>();

		FString OptionName = ConvertItemOptionName(Option.Type);

		EntryObject->SetOptionName(OptionName);
		EntryObject->SetOption(Option.Option);

		mOptionList->AddItem(EntryObject);
	}
}

void UItemInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}