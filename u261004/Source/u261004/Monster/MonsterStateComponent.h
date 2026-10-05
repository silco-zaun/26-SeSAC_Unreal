// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MonsterStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U261004_API UMonsterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStateComponent();

protected:
	UPROPERTY(EditAnywhere)
	FString mName;

	UPROPERTY(EditAnywhere)
	float		mAttack = 10.f;

	UPROPERTY(EditAnywhere)
	float		mDefense = 10.f;

	UPROPERTY(EditAnywhere)
	float		mHP = 100.f;

	UPROPERTY(EditAnywhere)
	float		mHPMax = 100.f;

public:
	void SetName(const FString& Name)
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

public:
	const FString& GetName()	const
	{
		return mName;
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool AddHP(int32 HP);
};
