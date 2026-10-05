// Fill out your copyright notice in the Description page of Project Settings.


#include "DuskBlade.h"


ADuskBlade::ADuskBlade()
{
#if WITH_EDITOR
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Fab/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Melee_Dusk.Minion_Lane_Melee_Dusk'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
#endif

	mCapsule->SetCapsuleHalfHeight(83.f);
	mCapsule->SetCapsuleRadius(35.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -83.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(
		TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_DuskBlade.ABP_DuskBlade_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	mInfoName = TEXT("DuskBlade");
}

void ADuskBlade::BeginPlay()
{
	Super::BeginPlay();
}

void ADuskBlade::OnConstruction(const FTransform& Transform)
{
	AMonsterPawn::OnConstruction(Transform);
}

void ADuskBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADuskBlade::Attack()
{

}
