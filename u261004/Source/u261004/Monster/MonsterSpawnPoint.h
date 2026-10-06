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
	FTimerHandle mSpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterSpawnPoint")
	float mSpawnDelay = 20.f;

	uint8 mWave = 1;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnTimerCallback();
	void SpawnMonster();

public:
	void MonsterChange();

};
