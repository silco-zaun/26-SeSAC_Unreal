// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_WukongAttack.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UAnimNotify_WukongAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference);
};
