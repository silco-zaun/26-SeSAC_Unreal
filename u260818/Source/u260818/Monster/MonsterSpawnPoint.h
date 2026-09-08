// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnPoint.generated.h"

UENUM(BlueprintType)
enum class EMonsterSpawnType : uint8
{
	Once,
	Loop
};

UCLASS()
class U260818_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnPoint();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	TObjectPtr<USplineComponent> mPatrolPath;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> mArrow;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	TSubclassOf<class AMonsterBase> mSpawnClass;

	TObjectPtr<class AMonsterBase> mSpawnMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	EMonsterSpawnType mSpawnType = EMonsterSpawnType::Loop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	float mSpawnDelay = 0.f;

	FTimerHandle mSpawnTimerHandle;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> mPatrolPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void ResetSpawn();

private:
	void SpawnTimerCallback();
	void SpawnMonster();
};
