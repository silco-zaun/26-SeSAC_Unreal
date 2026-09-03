// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterNormalAnim.generated.h"

UENUM(BlueprintType)
enum class EMonsterNormalAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death
};

/**
 * 
 */
UCLASS()
class U260818_API UMonsterNormalAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterNormalAnim();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterNormalAnimType mAnimType = EMonsterNormalAnimType::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mHitAlpha = 0.f;

public:
	void SetAnimType(EMonsterNormalAnimType Type)
	{
		mAnimType = Type;
	}

	void HitEnable()
	{
		mHitAlpha = 1.f;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
