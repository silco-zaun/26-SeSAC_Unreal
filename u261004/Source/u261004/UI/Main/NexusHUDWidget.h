// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "NexusHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API UNexusHUDWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UNexusHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> mHPBar;

protected:
	virtual void NativeOnInitialized();

public:
	void SetNexusHP(float HP, float HPMax);
};
