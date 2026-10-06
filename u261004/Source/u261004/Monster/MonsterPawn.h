// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "MonsterPawn.generated.h"

UCLASS()
class U261004_API AMonsterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonsterPawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMonsterAnimInstance> mAnimInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMonsterStateComponent> mState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFloatingPawnMovement> mMovement;

	FName mInfoName;
	TObjectPtr<class AMonsterSpawnPoint> mSpawnPoint;
	TObjectPtr<UBehaviorTree> mBehaviorTree;

	FMonsterDeath mMonsterDeath;

public:
	UCapsuleComponent* GetCapsule()	const
	{
		return mCapsule;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint)
	{
		mSpawnPoint = SpawnPoint;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void ChangeAnim(uint8 AnimType);
	virtual void Attack();
	virtual void AttackEnd();

public:
	UFUNCTION()
	void InfoLoadComplete();

public:
	template <typename T>
	void AddMonsterDeathCallback(T* Obj, void (T::* Func)(void))
	{
		mMonsterDeath.AddUObject(Obj, Func);
	}
};
