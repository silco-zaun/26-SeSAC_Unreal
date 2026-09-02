// Fill out your copyright notice in the Description page of Project Settings.


#include "Wukong.h"
#include "MainPlayerState.h"
#include "PlayerAnimInstance.h"

// Sets default values
AWukong::AWukong()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
		TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Skins/GreatSage/Meshes/Wukong_GreatSage.Wukong_GreatSage'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -96.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mArm->SetRelativeLocation(FVector(0.0, 0.0, 176.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));

	// 애니메이션 블루프린트 클래스를 얻어온다.
	// 클래스 정보를 찾아올 때 경로의 가장 끝에 _C를 무조건 붙여야 한다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		PlayerAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/ABP_Wukong.ABP_Wukong_C'"));

	if (PlayerAnim.Succeeded())
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	else
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			TEXT("Not Valid PlayerAnim"));
}

// Called when the game starts or when spawned
void AWukong::BeginPlay()
{
	Super::BeginPlay();

	// MainPlayerState를 얻어온다.
	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();

	if (IsValid(State))
	{
		State->SetPlayerName(TEXT("Wukong"));
		State->SetAttack(30.f);
		State->SetDefense(20.f);
		State->SetHP(500.f);
		State->SetHPMax(500.f);
		State->SetMP(100.f);
		State->SetMPMax(100.f);
		State->SetLevel(1);
		State->SetExp(0);
		State->SetGold(10000);
		State->SetMoveSpeed(600.f);
		State->SetAttackDistance(200.f);
	}
}

// Called every frame
void AWukong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWukong::Attack()
{
	TArray<FHitResult> HitArray;

	// GetActorLocation : 이 엑터의 위치를 얻어온다.
	FVector Start = GetActorLocation() + GetActorForwardVector() *
		(GetCapsuleComponent()->GetScaledCapsuleRadius() + 50.f);
	FVector End = Start + GetActorForwardVector() * 200.f;

	FCollisionQueryParams param(NAME_None, false, this);
	//param.AddIgnoredActor();

	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Start, End,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.f), param);

	// 디버깅용으로 캡슐을 그린다.
	FColor DebugColor = Hit ? FColor::Red : FColor::Green;

#if WITH_EDITOR
	FQuat Rot = FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat();

	float HalfHeight = (End - Start).Size() * 0.5f + 50.f;

	// 에디터에서는 충돌체를 그려준다.
	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, 100.f, 50.f,
		Rot, DebugColor, false, 1.f);
#endif

	if (Hit)
	{
		//AMainPlayerState* State = 

		// 차례대로 하나씩 꺼내며 반복한다.
		for (auto Result : HitArray)
		{
			// GetActor 함수를 이용해서 부딪힌 엑터를 얻어올 수 있다.
			FDamageEvent DmgEvent;
			Result.GetActor()->TakeDamage(10.f, DmgEvent, GetController(),
				this);
			
			TObjectPtr<USoundBase> HitSound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

			if (IsValid(HitSound))
			{
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
					HitSound, Result.ImpactPoint);
			}

			TObjectPtr<UParticleSystem> HitParticle =
				LoadObject<UParticleSystem>(GetWorld(),
					TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSunWukong/FX/Particles/Wukong/Abilities/Primary/FX/P_Wukong_Impact_Empowered.P_Wukong_Impact_Empowered'"));

			if (IsValid(HitParticle))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					HitParticle, Result.ImpactPoint);
			}
		}
	}
}

void AWukong::Death()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	GetMesh()->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	GetMesh()->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	GetMesh()->SetAllBodiesSimulatePhysics(false);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("pelvis"), true,
		true);

	// 바디의 Sleep 상태를 깨워준다.
	GetMesh()->WakeAllRigidBodies();

	// 애니메이션 포즈와 물리 결과를 섞어서 반영하도록 한다.
	GetMesh()->bBlendPhysics = true;

	//SetLifeSpan(3.f);
}

void AWukong::Skill1()
{
	mAnimInst->PlaySkill1();
}

void AWukong::Skill1Release()
{
}
