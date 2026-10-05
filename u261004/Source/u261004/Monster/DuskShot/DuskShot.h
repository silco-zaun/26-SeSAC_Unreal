// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterPawn.h"
#include "DuskShot.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API ADuskShot : public AMonsterPawn
{
	GENERATED_BODY()

public:
	ADuskShot();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
	virtual void Attack();
};
