// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "NexusHUDWidget.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mResultText->SetText(FText::FromString(""));
}

void UMainWidget::SetWaveText(const FString& WaveName)
{
	mWaveText->SetText(FText::FromString(WaveName));
}

void UMainWidget::SetMonsterText(const FString& MonsterText)
{
	mMonsterText->SetText(FText::FromString(MonsterText));
}

void UMainWidget::SetResultText(const FString& ResultText)
{
	mResultText->SetText(FText::FromString(ResultText));
}

void UMainWidget::SetNexusHP(float HP, float HPMax)
{
	mNexusHUD->SetNexusHP(HP, HPMax);
}

