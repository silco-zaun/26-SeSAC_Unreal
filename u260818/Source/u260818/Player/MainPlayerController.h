// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

protected:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> mMainWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMainWidget> mMainWidget;

public:
	class UMainWidget* GetMainWidget() const
	{
		return mMainWidget;
	}

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;
};
