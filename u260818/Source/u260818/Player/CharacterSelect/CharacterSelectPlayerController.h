// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "CharacterSelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API ACharacterSelectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterSelectPlayerController();

private:
	TSubclassOf<UUserWidget> mWidgetClass;
	TObjectPtr<class USelectWidget> mWidget;

	class ASelectPawn* mSelectPawn = nullptr;
	TObjectPtr<ACameraActor> mMainCamera;
	ACameraActor* mCurrentCamera = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual bool InputKey(const FInputKeyEventArgs& Params);

public:
	UFUNCTION()
	void ClickActor(AActor* TouchActor, FKey key);
};
