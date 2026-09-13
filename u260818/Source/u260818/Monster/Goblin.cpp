// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"
#include "MonsterStateComponent.h"
#include "../Player/PlayerCharacter.h"

AGoblin::AGoblin()
{
	mInfoName = TEXT("Goblin");

#if WITH_EDITOR
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Core_Dawn.Minion_Lane_Melee_Core_Dawn'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
#endif

	mCapsule->SetCapsuleHalfHeight(85.f);
	mCapsule->SetCapsuleRadius(35.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -85.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_Goblin.ABP_Goblin_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
}

void AGoblin::BeginPlay()
{
	Super::BeginPlay();
}

void AGoblin::OnConstruction(const FTransform& Transform)
{
	AMonsterBase::OnConstruction(Transform);
}

void AGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoblin::Attack()
{
	UBlackboardComponent* Blackboard = GetController<AAIController>()->GetBlackboardComponent();

	if (Blackboard)
	{
		AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(TEXT("Target")));

		if (Target)
		{
			FDamageEvent DmgEvent;
			Target->TakeDamage(mState->GetAttack(), DmgEvent,
				GetController(), this);

			FVector ImpactLocation = mMesh->GetSocketLocation(TEXT("FX_MeleeImpact"));

			// 만약 플레이어라면 플레이어의 위치를 얻어온다.
			APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(Target);

			if (IsValid(PlayerChar))
			{
				ImpactLocation = PlayerChar->GetImpactLocation();
			}

			TObjectPtr<USoundBase> HitSound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

			if (IsValid(HitSound))
			{
				// ImpactPoint는 부딪힌 위치이다.
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
					HitSound, ImpactLocation);
			}

			TObjectPtr<UParticleSystem> HitParticle =
				LoadObject<UParticleSystem>(GetWorld(),
					TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSunWukong/FX/Particles/Wukong/Abilities/Primary/FX/P_Wukong_Impact_Empowered.P_Wukong_Impact_Empowered'"));

			if (IsValid(HitParticle))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					HitParticle, ImpactLocation);
			}
		}
	}
}
