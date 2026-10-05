// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"


void UBaseAttributeSet::PostGameplayEffectExecute(
	const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute,
	float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// HP나 MP는 HPMax나 MPMax를 초과할 수 없다.
	if (Attribute == GetHPAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetHPMax());
	else if (Attribute == GetMPAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMPMax());
}

void UBaseAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute,
	float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UBaseAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute,
	float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UBaseAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute,
	float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}
