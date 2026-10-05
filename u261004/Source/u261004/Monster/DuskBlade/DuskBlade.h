// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterPawn.h"
#include "DuskBlade.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API ADuskBlade : public AMonsterPawn
{
	GENERATED_BODY()
	
public:
	ADuskBlade();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
	virtual void Attack();
};
