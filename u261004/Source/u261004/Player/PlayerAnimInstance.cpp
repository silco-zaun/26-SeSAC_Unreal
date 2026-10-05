// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* CharacterMovement =
			PlayerCharacter->GetCharacterMovement();
		
		mMoveSpeed = CharacterMovement->Velocity.Length();

		// 공중에 떠있는 상태인지 체크한다.
		mAir = CharacterMovement->IsFalling();

		// 가속도가 있는지 체크한다.
		mAccelerating = 
			CharacterMovement->GetCurrentAcceleration().Length() > 0.f;
	}
}

void UPlayerAnimInstance::PlayAttack()
{
	// 공격용 몽타주가 없을 경우 재생하지 않는다.
	if (!IsValid(mAttackMontage))
	{
		UE_LOG(LogTestDebug, Warning, 
			TEXT("Invalid Attack Montage"));
		return;
	}

	if (mAttackCombo)
	{
		Montage_Play(mAttackMontage, 1.f);

		mAttackCombo = false;
	}
	
}

void UPlayerAnimInstance::AnimNotify_Combo()
{
	mAttackCombo = true;
}
