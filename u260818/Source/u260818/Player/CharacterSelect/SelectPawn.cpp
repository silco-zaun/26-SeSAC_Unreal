// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"
#include "CharacterSelectPlayerController.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));

	SetRootComponent(mCapsule);

	mMesh->SetupAttachment(mCapsule);

	mCapture->SetupAttachment(mMesh);

	mCapsule->SetCapsuleHalfHeight(92.f);
	mCapsule->SetCapsuleRadius(38.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mCapsule->SetCollisionProfileName(TEXT("SelectPawn"));

	mCapture->SetRelativeLocation(FVector(0.0, 280.0, 110.0));
	mCapture->SetRelativeRotation(FRotator(0.0, -90.0, 0));

	mCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	mCapture->CaptureSource = SCS_SceneColorSceneDepth;
	mCapture->ShowOnlyActors.Add(this);
}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(GetWorld()->GetFirstPlayerController<ACharacterSelectPlayerController>(),
		&ACharacterSelectPlayerController::ClickActor);
}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Called to bind functionality to input
void ASelectPawn::EnableOutLine(bool Enable)
{
	mMesh->SetRenderCustomDepth(Enable);
}

