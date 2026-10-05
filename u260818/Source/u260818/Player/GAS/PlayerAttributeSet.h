// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GAS/BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAttributeSet", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Job;

public:
	ATTRIBUTE_FUNCTION(UPlayerAttributeSet, Job)
};
