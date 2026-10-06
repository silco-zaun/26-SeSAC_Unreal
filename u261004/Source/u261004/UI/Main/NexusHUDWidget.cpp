// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusHUDWidget.h"


UNexusHUDWidget::UNexusHUDWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UNexusHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UNexusHUDWidget::SetNexusHP(float HP, float HPMax)
{
	mHPBar->SetPercent(HP / HPMax);
}
