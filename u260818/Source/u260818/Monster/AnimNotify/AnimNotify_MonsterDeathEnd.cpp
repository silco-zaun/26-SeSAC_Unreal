// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MonsterDeathEnd.h"
#include "../MonsterBase.h"

void UAnimNotify_MonsterDeathEnd::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// SkeletalMeshComponent를 가지고 있는 Actor를 얻어온다.
	TObjectPtr<AMonsterBase> Monster =
		MeshComp->GetOwner<AMonsterBase>();

	if (IsValid(Monster))
		Monster->DeathEnd();
}
