// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect_CoolDown.h"


UGameplayEffect_CoolDown::UGameplayEffect_CoolDown()
{
	// INstant : 즉시 동작.
	// HasDuration : 지속시간이 존재.
	// Infinite : 무한 지속.
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	// 고정값 적용
	//DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));

	FSetByCallerFloat CoolDownDuration;

	CoolDownDuration.DataTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.CoolDown"));

	DurationMagnitude = FGameplayEffectModifierMagnitude(CoolDownDuration);
}
