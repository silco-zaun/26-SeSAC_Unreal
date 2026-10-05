// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacter.h"
#include "Crunch.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API ACrunch : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACrunch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack() override;
};
