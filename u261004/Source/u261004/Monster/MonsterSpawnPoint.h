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
class U261004_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnPoint();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	TObjectPtr<USceneComponent> mRoot;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> mArrow;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	TSubclassOf<class AMonsterPawn> mSpawnClass;

	UPROPERTY()
	TArray<TObjectPtr<class AMonsterPawn>> mSpawnMonsters;

	UPROPERTY()
	int32 Wave = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	//EMonsterSpawnType mSpawnType = EMonsterSpawnType::Loop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	float mSpawnDelay = 0.f;
	
	UPROPERTY()
	FTimerHandle mSpawnTimerHandle;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> mSpawnPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void ResetSpawn();

private:
	void SpawnTimerCallback();
	void SpawnMonster();
};
