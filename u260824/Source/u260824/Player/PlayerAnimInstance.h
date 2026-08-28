// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U260824_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAccelerating = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mViewYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mViewPitch = 0.f;

};
