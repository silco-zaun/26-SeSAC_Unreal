// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

UPlayerHUDWidget::UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerHUDWidget::SetPlayerName(const FString& Name)
{
	mName->SetText(FText::FromString(Name));
}

void UPlayerHUDWidget::SetPlayerHP(float HP, float HPMax)
{
	mHPBar->SetPercent(HP / HPMax);
}

void UPlayerHUDWidget::SetPlayerMP(float MP, float MPMax)
{
	mMPBar->SetPercent(MP / MPMax);
}
