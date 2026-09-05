// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterNormal.h"
#include "Goblin.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AGoblin : public AMonsterNormal
{
	GENERATED_BODY()
	
public:
	AGoblin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
};
