// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

AMainPlayerState::AMainPlayerState()
{
	UE_LOG(LogTestOrder, Warning, TEXT("AMainPlayerState::Constructor - %s"), *GetName());
}

bool AMainPlayerState::AddHP(int32 HP)
{
	UE_LOG(LogTestDebug, Warning, TEXT("HP : %.1f / %.1f"), mHP, mHPMax);

	mHP += HP;

	if (mHP > mHPMax)
		mHP = mHPMax;
	else if (mHP < 0.f)
	{
		mHP = 0.f;
	}

	if (mHPChange.IsBound())
		mHPChange.Broadcast(mHP, mHPMax);

	if (mHP <= 0.f)
		return false;

	return true;
}
