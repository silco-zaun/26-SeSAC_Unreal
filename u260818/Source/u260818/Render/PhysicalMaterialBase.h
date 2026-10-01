// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterialBase.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UPhysicalMaterialBase : public UPhysicalMaterial
{
	GENERATED_BODY()
	
public:
	UPhysicalMaterialBase(FVTableHelper& Helper);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterialBase)
	FString mMaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterialBase)
	TObjectPtr<USoundBase> mImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterialBase)
	TObjectPtr<UParticleSystem> mImpactParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterialBase)
	TObjectPtr<UNiagaraSystem> mImpactNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterialBase)
	TObjectPtr<UMaterialInterface> mDecalMaterial;

public:
	USoundBase* GetSound()
	{
		return mImpactSound;
	}

	UParticleSystem* GetParticle()
	{
		return mImpactParticle;
	}

public:
	virtual void PostLoad() override;
	virtual void FinishDestroy() override;
};
 