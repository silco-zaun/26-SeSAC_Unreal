// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterBase.h"
#include "GoblinArcher.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AGoblinArcher : public AMonsterBase
{
	GENERATED_BODY()

public:
	AGoblinArcher();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
};
