// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Riktor.generated.h"

/**
 * 
 */
UCLASS()
class U260824_API ARiktor : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ARiktor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
