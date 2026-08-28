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

	// 생성한 컴포넌트를 Root로 만든다.
	// Root 컴포넌트는 World(절대)좌표를 따른다.
	SetRootComponent(mMesh);

	// mChildMesh의 부모 컴포넌트로 mMesh를 지정한다.
	mChildMesh->SetupAttachment(mMesh);

	// SetRelativeLocation : 부모로부터 얼마나 떨어져있는지에 대한
	// 상대 위치를 지정하는 함수이다.
	mChildMesh->SetRelativeLocation(FVector(300.0, 0.0, 0.0));

	// RotMove가 업데이트할 컴포넌트를 지정한다.
	mRotMovement->SetUpdatedComponent(mMesh);

	// StaticMesh를 불러온다.
	// FObjectFinder를 이용해서 StaticMesh를 불러오는데 생성자에서
	// 에셋의 경로를 지정하면 불러온다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Script/Engine.StaticMesh'/Game/Cube1.Cube1'"));

	// 불러오는게 성공했다면 MeshComponent에 지정한다.
	// 불러온 Mesh는 FObjectFinder의 Object 변수에 저장되어 있다.
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

	// x축 -방향으로 이동하게 만든다.
	// Actor는 Transform이 없다. Actor의 Transform을 변경하는것은
	// RootComponent의 Transform을 변경하는것과 같다.
	// FVector는 X, Y, Z를 가지고 있는 백터 구조체이다.
	// X, Y, Z는 기본으로 double타입으로 되어 있다.
	AddActorWorldOffset(FVector(-200.0 * DeltaTime, 0.0, 0.0));

	// 짐벌락 : 축이 겹치는 현상
	//AddActorWorldRotation(FRotator(0.0, 180.0 * DeltaTime, 0.0));


}

