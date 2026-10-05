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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float mMana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float mHP;

	UPROPERTY(EditDefaultsOnly, BlueprintREadOnly, Category = "Ability")
	float mStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float mCoolDown;

public:
	virtual const FGameplayTagContainer* GetCooldownTags() const;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData);
};
