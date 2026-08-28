// Fill out your copyright notice in the Description page of Project Settings.


#include "Riktor.h"

ARiktor::ARiktor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRiktor/Characters/Heroes/Riktor/Meshes/Riktor.Riktor'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(120.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -120.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mArm->SetRelativeLocation(FVector(0.0, 0.0, 176.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));


}

void ARiktor::BeginPlay()
{
	Super::BeginPlay();

}

void ARiktor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
