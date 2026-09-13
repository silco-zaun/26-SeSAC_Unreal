// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "../Subsystem/UISubsystem.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		Subsystem->AddWidget(mWidgetName, this);
	}
}

void UBaseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		Subsystem->RemoveWidget(mWidgetName);
	}
}

void UBaseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


