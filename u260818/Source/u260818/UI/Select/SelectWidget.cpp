// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"
#include "SelectInfoWidget.h"

USelectWidget::USelectWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	mWidgetName = TEXT("Select");
}

void USelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mStartButton->OnPressed.AddDynamic(this, &USelectWidget::StartPressed);
	mStartButton->OnReleased.AddDynamic(this, &USelectWidget::StartReleased);
	mStartButton->OnClicked.AddDynamic(this, &USelectWidget::StartClick);
}

void USelectWidget::StartPressed()
{

}

void USelectWidget::StartReleased()
{

}

void USelectWidget::StartClick()
{
	// 입력한 플레이어 이름을 얻어온다.
	FString PlayerName = mInputName->GetText().ToString();

	// 이름을 입력하지 않았을 경우
	if (PlayerName.IsEmpty())
		return;

	FString Options = FString::Printf(TEXT("Job=%d PlayerName=%s "),
		(int32)mSelectJob, *PlayerName);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true,
		Options);
}

void USelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}

void USelectWidget::EnableSelectInfo(bool Enable)
{
	if (Enable)
		mSelectInfo->SetVisibility(ESlateVisibility::Visible);
	else
		mSelectInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void USelectWidget::SetCharacterImage(EPlayerJob Job)
{
	mSelectInfo->SetCharacterImage(Job);
}
