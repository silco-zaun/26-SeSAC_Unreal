// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MonsterDeathEnd.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UAnimNotify_MonsterDeathEnd : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference);
};
