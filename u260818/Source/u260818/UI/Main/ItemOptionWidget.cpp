// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOptionWidget.h"
#include "ItemOptionEntryObject.h"


UItemOptionWidget::UItemOptionWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UItemOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UItemOptionWidget::SetData(UObject* EntryObject)
{
	UItemOptionEntryObject* Obj = Cast<UItemOptionEntryObject>(EntryObject);

	if (!Obj)
		return;

	mOptionName->SetText(FText::FromString(Obj->GetOptionName()));

	FString Option = FString::Printf(TEXT("%.2f"), Obj->GetOption());

	mOption->SetText(FText::FromString(Option));
}
