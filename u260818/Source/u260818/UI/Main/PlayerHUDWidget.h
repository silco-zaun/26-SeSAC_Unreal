// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UPlayerHUDWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> mHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> mMPBar;

protected:
	virtual void NativeOnInitialized();

public:
	void SetPlayerName(const FString& Name);
	void SetPlayerHP(float HP, float HPMax);
	void SetPlayerMP(float MP, float MPMax);
};
