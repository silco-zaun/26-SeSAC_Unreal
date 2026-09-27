// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "../BaseWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UStartWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UStartWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> mStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> mExitButton;

protected:
	virtual void NativeOnInitialized();

protected:
	UFUNCTION()
	void StartPressed();

	UFUNCTION()
	void StartReleased();

	UFUNCTION()
	void StartClick();

	UFUNCTION()
	void ExitPressed();

	UFUNCTION()
	void ExitReleased();

	UFUNCTION()
	void ExitClick();

};
