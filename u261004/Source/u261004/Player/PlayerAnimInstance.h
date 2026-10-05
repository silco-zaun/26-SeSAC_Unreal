// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API UPlayerAnimInstance : public UAnimInstance
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

	// 공격용 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> mAttackMontage;

	bool mAttackCombo = true;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayAttack();

public:
	// 노티파이 함수 생성방법 : void AnimNotify_노티파이이름() 으로 함수를
	// 만든다.
	UFUNCTION()
	void AnimNotify_Combo();
};
