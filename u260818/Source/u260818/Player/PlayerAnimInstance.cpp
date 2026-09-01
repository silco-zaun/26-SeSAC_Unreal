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

	// 몽타주 재생이 끝났다면 호출될 함수를 지정한다.
	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* PlayerChar =
		Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerChar))
	{
		UCharacterMovementComponent* Movement =
			PlayerChar->GetCharacterMovement();

		mMoveSpeed = Movement->Velocity.Length();

		// 공중에 떠있는 상태인지를 체크한다.
		mAir = Movement->IsFalling();

		// 가속도가 있는지 체크한다.
		float Acceleration = Movement->GetCurrentAcceleration().Length();

		mAccelerating = Acceleration > 0.f;
	}
}

void UPlayerAnimInstance::PlayAttack()
{
	if (mSkillEndable)
		return;

	// 공격용 몽타주가 없을 경우 재생하지 않는다.
	if (!IsValid(mAttackMontage))
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Not Valid Attack Montage"));
		return;
	}

	// 공격 섹션 이름이 설정되지 않았을 경우 재생하지 않는다.
	if (mAttackSectionNames.Num() == 0)
	{
		UE_LOG(Sac8Debug, Warning, TEXT("Attack Section Names Is Empty"));
		return;
	}

	if (mAttackCombo)
	{
		// 공격 몽타주가 재생중인지 판단한다.
		//if (!Montage_IsPlaying(mAttackMontage))
		{
			// 재생 위치를 현재 섹션의 시작지점으로 변경한다.
			Montage_SetPosition(mAttackMontage, 0.f);

			Montage_Play(mAttackMontage, 1.f);

			Montage_JumpToSection(mAttackSectionNames[mAttackSectionIndex],
				mAttackMontage);

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
				FString::FromInt(mAttackSectionIndex));

			mAttackCombo = false;

			mAttackSectionIndex = (mAttackSectionIndex + 1) %
				mAttackSectionNames.Num();

		}
	}

}

void UPlayerAnimInstance::PlayHit()
{
	UE_LOG(Sac8Debug, Warning, TEXT("PlayHit"));

	// Hit 몽타주가 재생중인지 판단한다.
	if (Montage_IsPlaying(mHitMontage))
		return;

	UE_LOG(Sac8Debug, Warning, TEXT("Montage_Play"));


	Montage_SetPosition(mHitMontage, 0.f);

	Montage_Play(mHitMontage);

	mHitAlpha = 1.f;
}

void UPlayerAnimInstance::PlaySkill1()
{
	// Hit 몽타주가 재생중인지 판단한다.
	if (Montage_IsPlaying(mSkill1Montage))
		return;

	mSkillEndable = true;
	mAttackCombo = true;
	mAttackSectionIndex = 0;

	Montage_SetPosition(mSkill1Montage, 0.f);

	Montage_Play(mSkill1Montage);
}

void UPlayerAnimInstance::PlaySkill1(const FString& SectionName)
{
}

void UPlayerAnimInstance::AnimNotify_Combo()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		TEXT("Combo"));

	mAttackCombo = true;
}

void UPlayerAnimInstance::AnimNotify_ComboEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		TEXT("ComboEnd"));

	mAttackCombo = false;
}

void UPlayerAnimInstance::AnimNotify_DeathEnd()
{
	APlayerCharacter* PlayerChar =
		Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerChar))
	{
		PlayerChar->Death();
	}
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool Interrupted)
{
	// 공격 몽타주 재생이 끝났는지 판단한다.
	if (mAttackMontage == Montage)
	{
		if (!Interrupted)
		{
			mAttackCombo = true;
			mAttackSectionIndex = 0;
		}
	}
	else if (mHitMontage == Montage)
	{
		if (!Interrupted)
		{
			mHitAlpha = 0.f;
		}
	}
	else if (mSkill1Montage == Montage)
	{
		mSkillEndable = false;
	}
}
