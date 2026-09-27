// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "SelectWidget.generated.h"

/**
 *
 */
UCLASS()
class U260818_API USelectWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	USelectWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> mStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> mInputName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class USelectInfoWidget> mSelectInfo;

	EPlayerJob mSelectJob = EPlayerJob::Knight;

public:
	void SetSelectJob(EPlayerJob Job)
	{
		mSelectJob = Job;
	}

protected:
	virtual void NativeOnInitialized();

protected:
	UFUNCTION()
	void StartPressed();

	UFUNCTION()
	void StartReleased();

	UFUNCTION()
	void StartClick();

public:
	void EnableStartButton(bool Enable);
	void EnableSelectInfo(bool Enable);
	void SetCharacterImage(EPlayerJob Job);
};
