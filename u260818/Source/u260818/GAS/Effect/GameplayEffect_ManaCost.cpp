// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect_ManaCost.h"
#include "../BaseAttributeSet.h"

UGameplayEffect_ManaCost::UGameplayEffect_ManaCost()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// AttributeSet이 가지고 있는 MP를 변경할 수 있게 한다.
	FGameplayModifierInfo ModifierInfo;

	ModifierInfo.Attribute = UBaseAttributeSet::GetMPAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;

	// 감소시킬 마나는 고정값이 아니기 때문에 SetByCaller를 사용한다.
	FSetByCallerFloat MPCaller;

	MPCaller.DataTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.MPCost"));

	// SetByCaller를 ModifierInfo에 넣어준다.
	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(MPCaller);

	Modifiers.Add(ModifierInfo);
}
