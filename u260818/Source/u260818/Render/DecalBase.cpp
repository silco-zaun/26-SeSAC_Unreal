// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalBase.h"

// Sets default values
ADecalBase::ADecalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADecalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADecalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

