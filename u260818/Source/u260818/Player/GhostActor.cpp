// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostActor.h"

// Sets default values
AGhostActor::AGhostActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mRoot);

	mMesh->SetupAttachment(mRoot);

	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterial(TEXT("/Script/Engine.Material'/Game/Materials/MT_Ghost.MT_Ghost'"));

	if (SourceMaterial.Succeeded())
		mSourceMaterial = SourceMaterial.Object;
}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mOpacity -= (DeltaTime / 1.f);

	for (auto& Mtrl : mMaterials)
	{
		Mtrl->SetScalarParameterValue(TEXT("Opacity"), mOpacity);
	}

	if (mOpacity <= 0.f)
	{
		Destroy();
	}

}

void AGhostActor::CopyPose(USkeletalMeshComponent* Mesh)
{
	// 복제할 SkeletalMesh를 지정한다.
	mMesh->SetSkeletalMesh(Mesh->SkeletalMesh);

	// Pose를 복제한다.
	mMesh->CopyPoseFromSkeletalComponent(Mesh);

	// Material을 컨트롤하기 위한 MaterialInstanceDynamic을 만들어준다.
	int32 MaterialCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < MaterialCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i,
			mSourceMaterial);

		Mtrl->BlendMode = EBlendMode::BLEND_TranslucentGreyTransmittance;

		mMaterials.Add(Mtrl);
	}
}

