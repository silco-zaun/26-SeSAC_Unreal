// Fill out your copyright notice in the Description page of Project Settings.


#include "DuskShot.h"


ADuskShot::ADuskShot()
{
#if WITH_EDITOR
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Fab/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Ranged_Dusk.Minion_Lane_Ranged_Dusk'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
#endif

	mCapsule->SetCapsuleHalfHeight(77.f);
	mCapsule->SetCapsuleRadius(35.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -77.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_DuskShot.ABP_DuskShot'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	mInfoName = TEXT("DuskShot");
}

void ADuskShot::BeginPlay()
{
	Super::BeginPlay();
}

void ADuskShot::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ADuskShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADuskShot::Attack()
{
}
