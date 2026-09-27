// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"


UStartWidget::UStartWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	mWidgetName = TEXT("Start");
}

void UStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mStartButton->OnPressed.AddDynamic(this, &UStartWidget::StartPressed);
	mStartButton->OnReleased.AddDynamic(this, &UStartWidget::StartReleased);
	mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartClick);

	mExitButton->OnPressed.AddDynamic(this, &UStartWidget::ExitPressed);
	mExitButton->OnReleased.AddDynamic(this, &UStartWidget::ExitReleased);
	mExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitClick);
}

void UStartWidget::StartPressed()
{
	PlayWidgetAnimation(TEXT("StartClick"));
}

void UStartWidget::StartReleased()
{
	PlayWidgetAnimation(TEXT("StartClick"), 0.f, 1.f, false);
}

void UStartWidget::StartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterSelect"));
}

void UStartWidget::ExitPressed()
{
	PlayWidgetAnimation(TEXT("ExitClick"));
}

void UStartWidget::ExitReleased()
{
	PlayWidgetAnimation(TEXT("ExitClick"), 0.f, 1.f, false);
}

void UStartWidget::ExitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr,
		EQuitPreference::Quit, false);
}
