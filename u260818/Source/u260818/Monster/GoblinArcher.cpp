// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinArcher.h"


AGoblinArcher::AGoblinArcher()
{
	mInfoName = TEXT("GoblinArcher");

#if WITH_EDITOR
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Ranged_Core_Dawn.Minion_Lane_Ranged_Core_Dawn'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
#endif

	mCapsule->SetCapsuleHalfHeight(85.0f);
	mCapsule->SetCapsuleRadius(35.f);

	mMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -85.0f));
	mMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_GoblinArcher.ABP_GoblinArcher_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
}

void AGoblinArcher::BeginPlay()
{
	Super::BeginPlay();
}

void AGoblinArcher::OnConstruction(const FTransform& Transform)
{
	AMonsterBase::OnConstruction(Transform);
}

void AGoblinArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
