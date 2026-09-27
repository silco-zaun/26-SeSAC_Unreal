// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectInfoWidget.h"


USelectInfoWidget::USelectInfoWidget(
	const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	mWidgetName = TEXT("SelectInfo");
}

void USelectInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void USelectInfoWidget::SetCharacterImage(EPlayerJob Job)
{
	switch (Job)
	{
	case EPlayerJob::Knight:
		UE_LOG(Sac8Debug, Warning, TEXT("Knight is selected."));
		mCharacterImage->SetBrushFromMaterial(mTargetMaterial[0]);
		break;
	case EPlayerJob::Archer:
		break;
	case EPlayerJob::Wizard:
		break;
	case EPlayerJob::Gunner:
		UE_LOG(Sac8Debug, Warning, TEXT("Gunner is selected."));
		mCharacterImage->SetBrushFromMaterial(mTargetMaterial[1]);
		break;
	default:
		break;
	}
}
