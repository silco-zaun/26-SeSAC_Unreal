// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch.h"
#include "../MainPlayerState.h"
#include "../../Monster/MonsterPawn.h"


// Sets default values
ACrunch::ACrunch()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CrunchSkeletalMesh(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Fab/ParagonCrunch/Characters/Heroes/Crunch/Meshes/Crunch.Crunch'"));

	if (CrunchSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(CrunchSkeletalMesh.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(135.5f);
	GetCapsuleComponent()->SetCapsuleRadius(55.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -135.5));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mArm->SetRelativeLocation(FVector(0.0, 0.0, 271));
	mArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));

	// 애니메이션 블루프린트 클래스를 얻어온다.
	// 클래스 정보를 찾아올때 경로의 가장 끝에 _C를 무조건 붙여야 한다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		PlayerAnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/ABP_Crunch.ABP_Crunch_C'"));

	if (PlayerAnimInstance.Succeeded())
		GetMesh()->SetAnimInstanceClass(PlayerAnimInstance.Class);
	else
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid PlayerAnimInstance"));

	mInfoName = TEXT("Crunch");
}

// Called when the game starts or when spawned
void ACrunch::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACrunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrunch::Attack()
{
	TArray<FHitResult> HitArray;

	// GetActorLocation : 이 엑터의 위치를 얻어온다.
	FVector Start = GetActorLocation() + GetActorForwardVector() *
		(GetCapsuleComponent()->GetScaledCapsuleRadius() + 50.f);
	FVector End = Start + GetActorForwardVector() * 200.f;
	float Radius = 50.f;

	FCollisionQueryParams param(NAME_None, false, this);

	GetWorld()->SweepMultiByChannel(HitArray, Start, End,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(Radius), param);

	bool Hit = HitArray.Num() > 0;

	FColor DebugColor = Hit ? FColor::Red : FColor::Green;

#if WITH_EDITOR
	FQuat Rotation = FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat();

	float HalfHeight = (End - Start).Size() * 0.5f;

	// 에디터에서는 충돌체를 그려준다.
	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, HalfHeight, Radius, 
		Rotation, DebugColor, false, 1.f);
#endif

	if (Hit)
	{
		AMainPlayerState* State = Cast<AMainPlayerState>(GetPlayerState());

		if (!IsValid(State))
		{
			UE_LOG(LogTestDebug, Warning, TEXT("Invalid MainPlayerState"));
			return;
		}

		// 차례대로 하나씩 꺼내며 반복한다.
		for (auto Result : HitArray)
		{
			AActor* Target = Result.GetActor();

			if (!IsValid(Target))
				continue;

			// GetActor 함수를 이용해서 부딪힌 엑터를 얻어올 수 있다.
			FDamageEvent DamageEvent;
			Target->TakeDamage(State->GetAttack(), DamageEvent,
				GetController(), this);
		}
	}
}
