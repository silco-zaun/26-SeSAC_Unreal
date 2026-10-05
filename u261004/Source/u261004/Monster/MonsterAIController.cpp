// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"


AMonsterAIController::AMonsterAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	mPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	mSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	mSight->SightRadius = 5000.f;
	mSight->LoseSightRadius = 5200.f;
	mSight->PeripheralVisionAngleDegrees = 180.f;
	// 적을 감지한 후 마지막 위치를 기억하고 있는 시간을 지정한다.
	// 0을 지정하면 시간제한이 없다.
	mSight->SetMaxAge(5.f);

	mSight->DetectionByAffiliation.bDetectEnemies = true;
	mSight->DetectionByAffiliation.bDetectFriendlies = false;
	mSight->DetectionByAffiliation.bDetectNeutrals = false;

	mPerception->ConfigureSense(*mSight);
	mPerception->SetDominantSense(mSight->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(TeamMonster));

	mPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::TargetPerceptionUpdated);

	SetPerceptionComponent(*mPerception);
}

void AMonsterAIController::SetSightRadius(float Radius)
{
	mSight->SightRadius = Radius;
	mSight->LoseSightRadius = Radius + 200.f;

	mPerception->ConfigureSense(*mSight);
}

void AMonsterAIController::SetAttackDistance(float Distance)
{
	if (!IsValid(Blackboard))
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid Blackboard"));
		return;
	}

	Blackboard->SetValueAsFloat(TEXT("AttackDistance"), Distance);
}

void AMonsterAIController::SetAITree(const FString& Path)
{
}

void AMonsterAIController::SetAITree(UBehaviorTree* BehaviorTree)
{
	mBehaviorTree = BehaviorTree;

	// BehaviorTree를 실행한다.
	RunBehaviorTree(mBehaviorTree);
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 강제로 주변을 탐색하게 갱신한다.
	mPerception->RequestStimuliListenerUpdate();
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterAIController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ETeamAttitude::Type AMonsterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	// OtherTeamAgent변수가 nullptr이면 인자로 들어온 OtherActor가
	// IGenericTeamAgentInterface를 상속받지 않은 클래스라는 의미이다.
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral;

	FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();

	if (OtherTeamId == FGenericTeamId(TeamNeutral))
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherTeamId ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;

}

void AMonsterAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!IsValid(Blackboard))
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid Blackboard"));
		return;
	}

	// 감지에 성공했을 경우
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTestDebug, Log, TEXT("Target : %s"), *Actor->GetName());

		Blackboard->SetValueAsObject(TEXT("Target"), Actor);
	}
	else
	{
		UE_LOG(LogTestDebug, Log, TEXT("Target lost"));

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}
}
