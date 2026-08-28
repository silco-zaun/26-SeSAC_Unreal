// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "PlayerCharacter.h"
#include "Wukong.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AWukong : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWukong();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack();
};
