// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterAnimType mAnimType = EMonsterAnimType::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mHitAlpha = 0.f;

public:
	void SetAnimType(EMonsterAnimType Type)
	{
		mAnimType = Type;
	}

	void HitEnable()
	{
		mHitAlpha = 1.f;
	}

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
