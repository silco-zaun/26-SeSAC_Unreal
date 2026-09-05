// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterBase.h"
#include "MonsterNormal.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API AMonsterNormal : public AMonsterBase
{
	GENERATED_BODY()
	
public:
	AMonsterNormal();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();
};
