// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNormal.h"
#include "MonsterController.h"
#include "MonsterNormalAnim.h"

AMonsterNormal::AMonsterNormal()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/BT_MonsterNormal.BT_MonsterNormal'"));

	if (BTAsset.Succeeded())
		mBehaviorTree = BTAsset.Object;
}

void AMonsterNormal::ChangeAnim(uint8 AnimType)
{
	mAnimInst->SetAnimType((EMonsterNormalAnimType)AnimType);
}

void AMonsterNormal::BeginPlay()
{
	Super::BeginPlay();

	mAnimInst = Cast<UMonsterNormalAnim>(mMesh->GetAnimInstance());
}

void AMonsterNormal::OnConstruction(const FTransform& Transform)
{
	AMonsterBase::OnConstruction(Transform);
}

void AMonsterNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterNormal::PossessedBy(AController* NewController)
{
	AMonsterController* MonsterController = Cast<AMonsterController>(NewController);

	if (IsValid(MonsterController))
	{
		MonsterController->SetAITree(mBehaviorTree);
	}

	Super::PossessedBy(NewController);
}

void AMonsterNormal::UnPossessed()
{
	Super::UnPossessed();
}