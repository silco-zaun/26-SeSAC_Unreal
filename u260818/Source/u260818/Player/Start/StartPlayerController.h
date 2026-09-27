// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStartPlayerController();

private:
	TSubclassOf<UUserWidget> mWidgetClass;

protected:
	virtual void BeginPlay() override;
};
