// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

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
