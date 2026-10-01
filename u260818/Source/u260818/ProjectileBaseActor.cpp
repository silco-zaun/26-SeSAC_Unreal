// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBaseActor.h"

// Sets default values
AProjectileBaseActor::AProjectileBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMovement->SetUpdatedComponent(mBody);

	mMovement->OnProjectileStop.AddDynamic(this, &AProjectileBaseActor::ProjectileStop);
}

// Called when the game starts or when spawned
void AProjectileBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBaseActor::ProjectileStop(const FHitResult& ImpactResult)
{
	StopCallback(ImpactResult);
}

void AProjectileBaseActor::StopCallback(const FHitResult& ImpactResult)
{
	Destroy();
}

