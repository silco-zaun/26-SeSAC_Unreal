// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GhostActor.generated.h"

UCLASS()
class U260818_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostActor();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPoseableMeshComponent> mMesh;

	TObjectPtr<UMaterialInterface> mSourceMaterial;

	TArray<TObjectPtr<UMaterialInstanceDynamic>> mMaterials;

	float mOpacity = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CopyPose(USkeletalMeshComponent* Mesh);
};
