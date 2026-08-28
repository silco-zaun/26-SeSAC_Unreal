// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트를 생성한다.
	// 언리얼엔진은 유니코드 문자열을 사용한다.
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Mesh"));

	mChildMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("ChildMesh"));

	mRotMovement = CreateDefaultSubobject<URotatingMovementComponent>(
		TEXT("RotMove"));

	SetRootComponent(mMesh);

	mChildMesh->SetupAttachment(mMesh);

	mChildMesh->SetRelativeLocation(FVector(300.0, 0.0, 0.0));

	mRotMovement->SetUpdatedComponent(mMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Script/Engine.StaticMesh'/Game/BasicShapes/Cube1.Cube1'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
		mChildMesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(FVector(-200.0 * DeltaTime, 0.0, 0.0));
}

