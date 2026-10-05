// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Base.h"

UGameplayAbility_Base::UGameplayAbility_Base()
{
}

const FGameplayTagContainer* UGameplayAbility_Base::GetCooldownTags() const
{
	return nullptr;
}

// Ability 활성화시 호출되는 함수. Ability의 로직을 구현하는 곳
void UGameplayAbility_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		// 어빌리티를 종료하고 싶다면 반드시 EndAbility를 호출해야 한다.
		// 그렇지 않으면 어빌리티가 끝나지 않고 계속 남아있게 된다.
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		
		return;
	}
}
