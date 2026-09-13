// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MonsterAttack.h"
#include "../MonsterBase.h"


// 이 노티파이를 사용하는 AnimationBlueprint가 지정된 SkeletalMeshComponent
// 의 주소가 전달된다.
void UAnimNotify_MonsterAttack::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// SkeletalMeshComponent를 가지고 있는 Actor를 얻어온다.
	TObjectPtr<AMonsterBase> Monster =
		MeshComp->GetOwner<AMonsterBase>();

	if (IsValid(Monster))
		Monster->Attack();
}
