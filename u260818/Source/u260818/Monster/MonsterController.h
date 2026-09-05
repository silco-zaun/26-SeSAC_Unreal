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

	TObjectPtr<UBehaviorTree> mBehaviorTree;

public:
	void SetDetectRange(float Range);
	void SetAttackDistance(float Distance);
	void SetAITree(const FString& Path);
	void SetAITree(UBehaviorTree* Tree);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnTarget(AActor* Actor, FAIStimulus Stimulus);

public:
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
};
