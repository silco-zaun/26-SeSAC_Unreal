// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MonsterAIContorller")
	TObjectPtr<UAIPerceptionComponent> mPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MonsterAIContorller")
	TObjectPtr<UAISenseConfig_Sight> mSight;

	TObjectPtr<UBehaviorTree> mBehaviorTree;

public:
	void SetSightRadius(float Radius);
	void SetAttackDistance(float Distance);
	void SetAITree(const FString& Path);
	void SetAITree(UBehaviorTree* BehaviorTree);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:
	// OnTargetPerceptionUpdated는 Dynamic Delegate라서 
	// AddDynamic으로 바인딩하는 함수는 반드시 UFUNCTION()이어야 합니다. 
	// 이게 없으면 리플렉션이 함수 이름을 찾지 못해 바인딩이 실패합니다.
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
