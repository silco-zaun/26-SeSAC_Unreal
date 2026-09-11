// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "MonsterStateComponent.h"
#include "../Subsystem/AssetSubsystem.h"
#include "MonsterSpawnPoint.h"
#include "MonsterController.h"
#include "../Item/ItemBox.h"

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

bool AMonsterBase::GetDeath()	const
{
	return mState->GetHP() <= 0;
}

int32 AMonsterBase::GetGold()	const
{
	return mState->GetGold();
}

int32 AMonsterBase::GetExp()	const
{
	return mState->GetExp();
}

void AMonsterBase::ChangeAnim(uint8 AnimType)
{
}

void AMonsterBase::Attack()
{
}

void AMonsterBase::AttackEnd()
{
	AMonsterController* AICtrl =
		GetController<AMonsterController>();

	if (IsValid(AICtrl))
	{
		AICtrl->GetBlackboardComponent()->SetValueAsBool(
			TEXT("AttackEnd"), true);
	}
}

void AMonsterBase::DeathEnd()
{
	Destroy();
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

		UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

		if (AssetSystem)
		{
			if (AssetSystem->GetLoadMonsterInfo())
			{
				// Drop 아이템 확률을 계산하고 정보를 넘겨준다.
				for (auto& Item : mDropItems)
				{
					// FRand() 함수는 0 ~ 1 사이의 float타입 난수를 얻어온다.
					float Percent = FMath::FRand();

					// RoundToFloat 함수는 소수점 자리를 가장 가까운 정수 값으로 반올림해서
					// float으로 반환해주는 함수이다.
					Percent = FMath::RoundToFloat(Percent * 10000.f) / 100.f;

					UE_LOG(Sac8Debug, Warning, TEXT("%s (%.2f <= %.2f)"), *Item.ItemKey, Percent, Item.Percent);

					if (Percent <= Item.Percent)
					{
						// 아이템 키를 이용해서 정보를 얻어온다.
						const FItemTableInfo* ItemInfo =
							AssetSystem->FindItemInfo(*Item.ItemKey);

						// 아이템 정보가 있을 경우 아이템을 생성한다.
						if (ItemInfo)
						{
							UE_LOG(Sac8Debug, Warning, TEXT("DropItem : %s"), *Item.ItemKey);
							// 칼, 갑옷, 체력회복물약중 1개를 랜덤하게 가지고 있는
							// 상자를 만들어보자.
							FActorSpawnParameters param;
							param.SpawnCollisionHandlingOverride =
								ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

							FVector ItemLoc;

							GetRandomNavigationPoint(ItemLoc, GetWorld(),
								GetActorLocation(), 100.f);

							ItemLoc.Z += 80.0;

							AItemBox* ItemBox = GetWorld()->SpawnActor<AItemBox>(
								ItemLoc, FRotator::ZeroRotator, param);

							ItemBox->SetItemInfo(ItemInfo);
						}
					}
				}
			}
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

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	if (DamageAmount > 0.f)
	{
		DamageAmount = DamageAmount - mState->GetDefense();

		DamageAmount = FMath::Max(DamageAmount, 1.f);

		UE_LOG(Sac8Debug, Warning, TEXT("Damage(M) : %.2f"), DamageAmount);

		if (!mState->AddHP(-DamageAmount))
		{
			//Destroy();
			// 죽는 모션을 재생한다.
			ChangeAnim((uint8)EMonsterNormalAnimType::Death);

			// 인공지능을 멈춘다.
			AAIController* AI = GetController<AAIController>();

			AI->BrainComponent->StopLogic(TEXT("Death"));
			AI->BrainComponent->Cleanup();
			AI->StopMovement();

			mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			// Component 비활성화.
			mMovement->Deactivate();

			// Tick 비활성화
			mMovement->SetComponentTickEnabled(false);
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

			mDropItems = Info->DropItems;

			AMonsterController* AICtrl =
				GetController<AMonsterController>();

			if (IsValid(AICtrl))
			{
				AICtrl->SetDetectRange(Info->DetectRange);
				AICtrl->SetAttackDistance(Info->AttackDistance);
			}
		}
	}
}
