// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MonsterController")
	TObjectPtr<UAIPerceptionComponent> mPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MonsterController")
	TObjectPtr<UAISenseConfig_Sight> mSight;


};
