// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UPlayerAnimInstance : public UAnimInstance
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

	// 공격용 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> mAttackMontage;

	// 에디터에서 편집 가능한 변수를 만든다.
	UPROPERTY(EditAnywhere)
	TArray<FName> mAttackSectionNames;

	int32 mAttackSectionIndex = 0;

	bool mAttackCombo = true;

public:
	void AddViewYaw(float Yaw)
	{
		mViewYaw += Yaw;
	}

	void AddViewPitch(float Pitch)
	{
		mViewPitch += Pitch;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayAttack();

public: // Notify
	// 노티파이 함수 생성방법 : void AnimNotify_노티파이이름() 으로 함수를
	// 만든다.
	UFUNCTION()
	void AnimNotify_Combo();

	UFUNCTION()
	void AnimNotify_ComboEnd();

protected:
	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool Interrupted);
};
