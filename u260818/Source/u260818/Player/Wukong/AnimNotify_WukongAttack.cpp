// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_WukongAttack.h"
#include "../PlayerCharacter.h"

// 이 노티파이를 사용하는 AnimationBlueprint가 지정된 SeletalMeshCompnent
// 의 주소가 전달된다.
void UAnimNotify_WukongAttack::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// SkeletalMeshComponent를 가지고 있는 Actor를 얻어온다.
	TObjectPtr<APlayerCharacter> PlayerChar =
		MeshComp->GetOwner<APlayerCharacter>();

	if (IsValid(PlayerChar))
		PlayerChar->Attack();
}

