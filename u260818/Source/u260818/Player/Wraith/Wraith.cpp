// Fill out your copyright notice in the Description page of Project Settings.


#include "Wraith.h"
#include "../MainPlayerState.h"

// Sets default values
AWraith::AWraith()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Skins/LunarOps/Meshes/Wraith_LunarOps.Wraith_LunarOps'"));

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
		PlayerAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/ABP_Wraith.ABP_Wraith_C'"));

	if (PlayerAnim.Succeeded())
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);

	mInfoName = TEXT("Wraith");
}

// Called when the game starts or when spawned
void AWraith::BeginPlay()
{
	Super::BeginPlay();

	// MainPlayerState를 얻어온다.
	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();

	if (IsValid(State))
	{
		State->SetPlayerName(TEXT("Wraith"));
		State->SetAttack(20.f);
		State->SetDefense(15.f);
		State->SetHP(400.f);
		State->SetHPMax(400.f);
		State->SetMP(200.f);
		State->SetMPMax(200.f);
		State->SetLevel(1);
		State->SetExp(0);
		State->SetGold(10000);
		State->SetMoveSpeed(500.f);
		State->SetAttackDistance(500.f);
	}
}



// Called every frame
void AWraith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWraith::Attack()
{
}