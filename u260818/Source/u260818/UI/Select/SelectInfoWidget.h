// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "SelectInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API USelectInfoWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	USelectInfoWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> mCharacterImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mDefense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mHP;

	EPlayerJob mSelectJob = EPlayerJob::Knight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TArray<TObjectPtr<UMaterialInterface>> mTargetMaterial;

public:

protected:
	virtual void NativeOnInitialized();

public:
	void SetCharacterImage(EPlayerJob Job);
};
