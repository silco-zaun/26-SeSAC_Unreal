// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterPatrol.h"
#include "../MonsterBase.h"

UBTTask_MonsterPatrol::UBTTask_MonsterPatrol()
{
	NodeName = TEXT("MonsterPatrol");

	// Tick을 호출할 수 있게 한다.
	bNotifyTick = true;

	// Task가 끝났을 때, OnTaskFinished를 호출할 수 있게 한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MonsterPatrol::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return EBTNodeResult::Failed;

	// OwnerComp가 가지고 있는 BlackboardComponent를 얻어온다.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!BlackboardComp)
		return EBTNodeResult::Failed;

	// 블랙보드에서 Target을 얻어온다.
	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));

	if (Target)
		return EBTNodeResult::Failed;

	AMonsterBase* Monster = AIController->GetPawn<AMonsterBase>();

	if (!Monster)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterPatrol::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	// AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	// OwnerComp가 가지고 있는 BlackboardComponent를 얻어온다.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	// 블랙보드에서 Target을 얻어온다.
	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));

	if (Target)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	AMonsterBase* Monster = AIController->GetPawn<AMonsterBase>();

	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}

void UBTTask_MonsterPatrol::OnTaskFinished(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	AIController->StopMovement();
}
