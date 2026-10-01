// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalBase.generated.h"

UCLASS()
class U260818_API ADecalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	TObjectPtr<UDecalComponent> mDecal;

	TObjectPtr<UMaterialInstanceDynamic> mDecalDynamicMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDecalMaterial(UMaterialInterface* Material);
	void SetDecalMaterial(const FString& Path);
	void ChangeDynamicMaterialDecal();
};
