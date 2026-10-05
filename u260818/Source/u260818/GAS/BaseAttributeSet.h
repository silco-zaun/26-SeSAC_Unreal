// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	Exp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	Gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData	AttackDistance;

public:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data);
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const;

public:
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, Attack)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, Defense)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, HP)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, HPMax)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, MP)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, MPMax)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, Level)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, Exp)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, Gold)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, MoveSpeed)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, AttackSpeed)
	ATTRIBUTE_FUNCTION(UBaseAttributeSet, AttackDistance)
};
