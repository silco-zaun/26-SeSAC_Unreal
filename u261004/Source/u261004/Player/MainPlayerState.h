// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class U261004_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMainPlayerState();

protected:
	UPROPERTY(EditAnywhere)
	FString mName;

	UPROPERTY(EditAnywhere)
	float		mAttack = 20.f;

	UPROPERTY(EditAnywhere)
	float		mDefense = 10.f;

	UPROPERTY(EditAnywhere)
	float		mHP = 100.f;

	UPROPERTY(EditAnywhere)
	float		mHPMax = 100.f;

	FHPChange mHPChange;

public:
	void SetPlayerName(const FString& Name)
	{
		mName = Name;
	}

	void SetAttack(float Attack)
	{
		mAttack = Attack;
	}

	void SetDefense(float Defense)
	{
		mDefense = Defense;
	}

	void SetHP(float HP)
	{
		mHP = HP;
	}

	void SetHPMax(float HP)
	{
		mHPMax = HP;
	}

	bool AddHP(int32 HP);

public:
	const FString& GetPlayerName() const
	{
		return mName;
	}

	float GetAttack() const
	{
		return mAttack;
	}

	float GetDefense() const
	{
		return mDefense;
	}

	float GetHP() const
	{
		return mHP;
	}

	float GetHPMax() const
	{
		return mHPMax;
	}

public:
	template <typename T>
	void AddHPChangeCallback(T* Obj, void (T::* Func)(float, float))
	{
		mHPChange.AddUObject(Obj, Func);
	}
};
