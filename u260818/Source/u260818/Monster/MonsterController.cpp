// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

AMonsterController::AMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;

	mPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	mSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	mSight->SightRadius = 500.f;
	mSight->LoseSightRadius = 600.f;
	mSight->PeripheralVisionAngleDegrees = 180.f;
	mSight->SetMaxAge(5.f);

	mSight->DetectionByAffiliation.bDetectEnemies = true;
	mSight->DetectionByAffiliation.bDetectFriendlies = true;
	mSight->DetectionByAffiliation.bDetectNeutrals = true;

	mPerception->ConfigureSense(*mSight);
	mPerception->SetDominantSense(mSight->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(TeamMonster));

	mPerception->OnTargetPerceptionUpdated.AddDynamic(this,
		&AMonsterController::OnTarget);

	SetPerceptionComponent(*mPerception);
}

void AMonsterController::SetDetectRange(float Range)
{
	mSight->SightRadius = Range;
	mSight->LoseSightRadius = Range + 200.f;

	mPerception->ConfigureSense(*mSight);
}

void AMonsterController::SetAttackDistance(float Distance)
{
	if (!IsValid(Blackboard))
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Invalid Blackboard"));

		return;
	}
	
	Blackboard->SetValueAsFloat(TEXT("AttackDistance"), Distance);
}

void AMonsterController::SetAITree(const FString& Path)
{
}

void AMonsterController::SetAITree(UBehaviorTree* Tree)
{
	mBehaviorTree = Tree;

	// BehaviorTree를 실행한다.
	RunBehaviorTree(mBehaviorTree);
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 강제로 주변을 탐색하게 갱신한다.
	mPerception->RequestStimuliListenerUpdate();
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterController::OnTarget(AActor* Actor, FAIStimulus Stimulus)
{
	if (!IsValid(Blackboard))
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Invalid Blackboard"));

		return;
	}

	// 감지에 성공했을 경우
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Target : %s"),
			*Actor->GetName());

		Blackboard->SetValueAsObject(TEXT("Target"), Actor);
	}
	else
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Target lost"));

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}
}

ETeamAttitude::Type AMonsterController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	// OtherTeamAgent변수가 nullptr이면 인자로 들어온 OtherActor가
	// IGenericTeamAgentInterface를 상속받지 않은 클래스라는 의미이다.
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral;
	else if (OtherTeamAgent->GetGenericTeamId() ==
		FGenericTeamId(TeamNeutral))
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}
