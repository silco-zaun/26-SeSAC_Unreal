// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "MonsterAnimInstance.h"
#include "MonsterStateComponent.h"
#include "MonsterAIController.h"
#include "../Subsystem/AssetSubsystem.h"

// Sets default values
AMonsterPawn::AMonsterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mState = CreateDefaultSubobject<UMonsterStateComponent>(TEXT("State"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	mMovement->SetUpdatedComponent(mCapsule);
	mMovement->MaxSpeed = 300.f;
	// 이동을 XY 평면으로 제한한다. (Z축 이동 차단)
	mMovement->SetPlaneConstraintEnabled(true);
	mMovement->SetPlaneConstraintNormal(FVector::UpVector);

	SetRootComponent(mCapsule);

	mMesh->SetupAttachment(mCapsule);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mCapsule->SetCollisionProfileName(TEXT("Monster"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTree(
		TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/BT_Monster.BT_Monster'"));

	if (BehaviorTree.Succeeded())
	{
		UE_LOG(LogTestDebug, Log, TEXT("Set BT_Monster"));
		mBehaviorTree = BehaviorTree.Object;
	}
	else
		UE_LOG(LogTestDebug, Log, TEXT("Invalid BT_Monster"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterAIController::StaticClass();

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	UAssetSubsystem* AssetSubsystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSubsystem)
	{
		if (AssetSubsystem->GetIsMonsterInfoLoadComplelte())
		{
			InfoLoadComplete();
		}
		else
		{
			AssetSubsystem->AddMonsterInfoLoadCompleteDelegate(this, &AMonsterPawn::InfoLoadComplete);
		}
	}

	mAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());
}

void AMonsterPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterPawn::PossessedBy(AController* NewController)
{
	AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(NewController);

	if (IsValid(MonsterAIController))
	{
		MonsterAIController->SetAITree(mBehaviorTree);
	}

	Super::PossessedBy(NewController);
}

void AMonsterPawn::UnPossessed()
{
	Super::UnPossessed();
}

float AMonsterPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, 
		EventInstigator, DamageCauser);

	if (DamageAmount > 0.f)
	{
		DamageAmount = DamageAmount - mState->GetDefense();

		DamageAmount = FMath::Max(DamageAmount, 0.f);

		UE_LOG(LogTestDebug, Log, TEXT("Damage : %.2f"), DamageAmount);

		if (!mState->AddHP(-DamageAmount))
		{
			Destroy();

			UE_LOG(LogTestDebug, Warning, TEXT("몬스터 사망"));

			if (mMonsterDeath.IsBound())
				mMonsterDeath.Broadcast();

			/*AAIController* AI = GetController<AAIController>();

			AI->BrainComponent->StopLogic(TEXT("Death"));
			AI->BrainComponent->Cleanup();
			AI->StopMovement();

			mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			mMovement->Deactivate();
			mMovement->SetComponentTickEnabled(false);*/
		}
	}

	return DamageAmount;
}

void AMonsterPawn::ChangeAnim(uint8 AnimType)
{
	mAnimInst->SetAnimType((EMonsterAnimType)AnimType);
}

void AMonsterPawn::Attack()
{
}

void AMonsterPawn::AttackEnd()
{
	AMonsterAIController* AICtrl = GetController<AMonsterAIController>();

	if (IsValid(AICtrl))
	{
		AICtrl->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnd"), true);
	}
}

void AMonsterPawn::InfoLoadComplete()
{
	UAssetSubsystem* AssetSubsystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSubsystem)
	{
		const FMonsterInfo* Info = AssetSubsystem->FindMonsterInfo(mInfoName);

		if (Info)
		{
			mState->SetName(Info->Name);
			mState->SetAttack(Info->Attack);
			mState->SetDefense(Info->Defense);
			mState->SetHP(Info->HP);
			mState->SetHPMax(Info->HPMax);

			mMesh->SetSkeletalMeshAsset(Info->Mesh);
		}
	}
}