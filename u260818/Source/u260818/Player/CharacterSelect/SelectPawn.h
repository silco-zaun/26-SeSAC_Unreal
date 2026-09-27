// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "SelectPawn.generated.h"

UCLASS()
class U260818_API ASelectPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectPawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ArrayClamp = "true"))
	TObjectPtr<UCapsuleComponent> mCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ArrayClamp = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ArrayClamp = "true"))
	TObjectPtr<USceneCaptureComponent2D> mCapture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ArrayClamp = "true"))
	EPlayerJob mJob;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ArrayClamp = "true"))
	TObjectPtr<ACameraActor> mViewCamera;

public:
	EPlayerJob GetPlayerJob() const
	{
		return mJob;
	}

	ACameraActor* GetViewCamera() const
	{
		return mViewCamera;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
