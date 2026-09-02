// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA
	// 에디터에서는 RootComponent가 어디에 있는지 표시해준다.
#endif
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawnPoint::ResetSpawn()
{
}

void AMonsterSpawnPoint::SpawnTimerCallback()
{
}

void AMonsterSpawnPoint::SpawnMonster()
{
}

