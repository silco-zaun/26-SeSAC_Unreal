// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_Base();

protected:
	FGameplayTag mCoolDownTag;

	// mutable은 const 함수 안에서도 이 변수만은 수정할 수 있게 허용한다.
	mutable FGameplayTagContainer mCoolDownTagsContainer;

	// 현재 Ability가 사용할 수 있는 Ability인지 판단하는 변수.
	bool mAbilityActive = true;

public:
	virtual const FGameplayTagContainer* GetCooldownTags() const override;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData);
};
