// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Nexus.generated.h"

UCLASS()
class U261004_API ANexus : public AActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANexus();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> mCapsule;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> mStimuliSource;

	FGenericTeamId mTeamId;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
