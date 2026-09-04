// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "MonsterStateComponent.h"
#include "../Subsystem/AssetSubsystem.h"
#include "MonsterSpawnPoint.h"
#include "MonsterController.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mState = CreateDefaultSubobject<UMonsterStateComponent>(TEXT("State"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	mMovement->SetUpdatedComponent(mCapsule);

	SetRootComponent(mCapsule);

	mMesh->SetupAttachment(mCapsule);
	mCapsule->SetCollisionProfileName(TEXT("Monster"));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterController::StaticClass();

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();
	
	if (AssetSystem)
	{
		if (AssetSystem->GetLoadPlayerInfo())
		{
			InfoLoadComplete();
		}
		else
		{
			AssetSystem->AddMonsterDataAssetLoadingDelegate(this, &AMonsterBase::InfoLoadComplete);
		}
	}

	UE_LOG(Sac8Debug, Warning, TEXT("Monster BeginPlay"));
}

void AMonsterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		if (IsValid(mSpawnPoint))
		{
			mSpawnPoint->ResetSpawn();
		}
	}
}

void AMonsterBase::OnConstruction(const FTransform& Transform)
{
	UE_LOG(Sac8Debug, Warning, TEXT("Monster OnConstruction"));
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMonsterBase::UnPossessed()
{
	Super::UnPossessed();
}

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	if (DamageAmount > 0.f)
	{
		DamageAmount = DamageAmount - mState->GetDefense();

		DamageAmount = FMath::Max(DamageAmount, 1.f);

		UE_LOG(Sac8Debug, Warning, TEXT("Damage : %.2f"), DamageAmount);

		if (!mState->AddHP(-DamageAmount))
		{
			Destroy();
		}
	}

	return DamageAmount;
}

void AMonsterBase::InfoLoadComplete()
{
	UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSystem)
	{
		const FMonsterInfo* Info = AssetSystem->FindMonsterInfo(mInfoName);

		if (Info)
		{
			mState->SetPlayerName(Info->MonsterName);
			mState->SetMonsterType(Info->MonsterType);
			mState->SetAttack(Info->Attack);
			mState->SetDefense(Info->Defense);
			mState->SetHP(Info->HP);
			mState->SetHPMax(Info->HP);
			mState->SetMP(Info->MP);
			mState->SetMPMax(Info->MP);
			mState->SetLevel(Info->Level);
			mState->SetExp(Info->Exp);
			mState->SetGold(Info->Gold);
			mState->SetMoveSpeed(Info->MoveSpeed);
			mState->SetAttackSpeed(Info->AttackSpeed);
			mState->SetAttackDistance(Info->AttackDistance);
			mState->SetDetectRange(Info->DetectRange);

			mMesh->SetSkeletalMeshAsset(Info->BodyMesh);

			mMovement->MaxSpeed = Info->MoveSpeed;

			AMonsterController* AICtrl =
				GetController<AMonsterController>();

			if (IsValid(AICtrl))
			{
				//AICtrl->SetDetectRange(Info->DetectRange);
				//AICtrl->SetAttackDistance(Info->AttackDistance);
			}
		}
	}
}

