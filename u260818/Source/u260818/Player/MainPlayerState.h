// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 *
 */
UCLASS()
class U260818_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMainPlayerState();

protected:
	UPROPERTY(EditAnywhere)
	FString		mName;

	UPROPERTY(EditAnywhere)
	EPlayerJob		mJob;

	UPROPERTY(EditAnywhere)
	float		mAttack = 0.f;

	UPROPERTY(EditAnywhere)
	float		mDefense = 0.f;

	UPROPERTY(EditAnywhere)
	float		mHP = 0.f;

	UPROPERTY(EditAnywhere)
	float		mHPMax = 0.f;

	UPROPERTY(EditAnywhere)
	float		mMP = 0.f;

	UPROPERTY(EditAnywhere)
	float		mMPMax = 0.f;

	UPROPERTY(EditAnywhere)
	int32		mLevel = 0;

	UPROPERTY(EditAnywhere)
	int32		mExp = 0;

	UPROPERTY(EditAnywhere)
	int32		mGold = 0;

	UPROPERTY(EditAnywhere)
	float		mMoveSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float		mAttackSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float		mAttackDistance = 200.f;

public:
	void SetPlayerName(const FString& Name)
	{
		mName = Name;
	}

	void SetPlayerJob(EPlayerJob Job)
	{
		mJob = Job;
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

	void SetMP(float MP)
	{
		mMP = MP;
	}

	void SetMPMax(float MP)
	{
		mMPMax = MP;
	}

	void SetLevel(int32 Level)
	{
		mLevel = Level;
	}

	void SetExp(int32 Exp)
	{
		mExp = Exp;
	}

	void SetGold(int32 Gold)
	{
		mGold = Gold;
	}

	bool AddHP(int32 HP)
	{
		mHP += HP;

		if (mHP > mHPMax)
			mHP = mHPMax;
		else if (mHP < 0.f)
		{
			mHP = 0.f;
			return false;
		}

		return true;
	}

	void AddGold(int32 Gold)
	{
		mGold += Gold;
	}

	void AddExp(int32 Exp)
	{
		mExp += Exp;

		if (mExp < 0)
			mExp = 0;
	}

	void SetMoveSpeed(float Speed)
	{
		mMoveSpeed = Speed;
	}

	void SetAttackSpeed(float Speed)
	{
		mAttackSpeed = Speed;
	}

	void SetAttackDistance(float Distance)
	{
		mAttackDistance = Distance;
	}

public:
	const FString& GetPlayerName()	const
	{
		return mName;
	}

	EPlayerJob GetPlayerJob()	const
	{
		return mJob;
	}

	float GetAttack()	const
	{
		return mAttack;
	}

	float GetDefense()	const
	{
		return mDefense;
	}

	float GetHP()	const
	{
		return mHP;
	}

	float GetHPMax()	const
	{
		return mHPMax;
	}

	float GetMP()	const
	{
		return mMP;
	}

	float GetMPMax()	const
	{
		return mMPMax;
	}

	int32 GetLevel()	const
	{
		return mLevel;
	}

	int32 GetExp()	const
	{
		return mExp;
	}

	int32 GetGold()	const
	{
		return mGold;
	}

	float GetMoveSpeed()	const
	{
		return mMoveSpeed;
	}

	float GetAttackSpeed()	const
	{
		return mAttackSpeed;
	}

	float GetAttackDistance()	const
	{
		return mAttackDistance;
	}
};
