// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

AMainPlayerState::AMainPlayerState()
{
	UE_LOG(Sac8Order, Warning, TEXT("AMainPlayerState::Constructor - %s"), *GetName());
}

bool AMainPlayerState::AddHP(int32 HP)
{
	mHP += HP;

	bool result = true;

	if (mHP > mHPMax)
		mHP = mHPMax;
	else if (mHP < 0.f)
	{
		mHP = 0.f;
		result = false;
	}

	if (mHPChange.IsBound())
		mHPChange.Broadcast(mHP, mHPMax);

	return result;
}