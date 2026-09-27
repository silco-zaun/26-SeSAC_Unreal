// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"

AStartPlayerController::AStartPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Start/WB_Start.WB_Start_C'"));

	if (WidgetClass.Succeeded())
		mWidgetClass = WidgetClass.Class;
}

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;

	SetInputMode(InputMode);

	if (IsValid(mWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), mWidgetClass);

		if (IsValid(Widget))
			Widget->AddToViewport();
	}
}
