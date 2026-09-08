// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "MonsterBase.generated.h"

UCLASS()
class U260818_API AMonsterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonsterBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMonsterStateComponent> mState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFloatingPawnMovement> mMovement;

	FName mInfoName;

	TObjectPtr<class AMonsterSpawnPoint> mSpawnPoint;

	TObjectPtr<UBehaviorTree> mBehaviorTree;

	TArray<FVector> mPatrolPoints;

public:
	UCapsuleComponent* GetCapsule()	const
	{
		return mCapsule;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint)
	{
		mSpawnPoint = SpawnPoint;
	}

	void SetPatrolPoints(const TArray<FVector>& PatrolPoints)
	{
		mPatrolPoints = PatrolPoints;
	}

public:
	virtual void ChangeAnim(uint8 AnimType);
	virtual void Attack();
	virtual void AttackEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();
	/**
	 * Apply damage to this actor.
	 * @see https://www.unrealengine.com/blog/damage-in-ue4
	 * @param DamageAmount		How much damage to apply
	 * @param DamageEvent		Data package that fully describes the damage received.
	 * @param EventInstigator	The Controller responsible for the damage.
	 * @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return					The amount of damage actually applied.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

public:
	UFUNCTION()
	void InfoLoadComplete();
};
