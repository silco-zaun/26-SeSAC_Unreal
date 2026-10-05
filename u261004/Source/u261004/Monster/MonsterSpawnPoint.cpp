// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "MonsterPawn.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA
	// 에디터에서는 RootComponent가 어디에 있는지 표시해준다.
	mRoot->bVisualizeComponent = true;

	mArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	mArrow->ArrowColor = FColor(255, 120, 130);
	mArrow->bTreatAsASprite = true;
	mArrow->bIsScreenSizeScaled = true;

	mArrow->SetupAttachment(mRoot);
#endif

	SetRootComponent(mRoot);
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnMonster();
}

void AMonsterSpawnPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

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
	GetWorldTimerManager().ClearTimer(mSpawnTimerHandle);

	SpawnMonster();
}

void AMonsterSpawnPoint::SpawnMonster()
{
	if (!IsValid(mSpawnClass))
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid SpawnClass"));
		return;
	}

	if (Wave < 1 || Wave > 3)
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid Wave"));
		return;
	}

	for (TObjectPtr<AMonsterPawn>& Monster : mSpawnMonsters)
	{
		if (IsValid(Monster))
			Monster->Destroy();
	}

	mSpawnMonsters.Empty();

	FVector SpawnPoint = GetActorLocation();

	// 생성할 클래스를 이용해서 CDO를 얻어올 수 있다.
	TObjectPtr<AMonsterPawn> MonsterCDO =
		mSpawnClass->GetDefaultObject<AMonsterPawn>();

	if (IsValid(MonsterCDO))
		SpawnPoint.Z += MonsterCDO->GetCapsule()->GetScaledCapsuleHalfHeight();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < Wave * 5; ++i)
	{
		FVector2D Rand = FMath::RandPointInCircle(300.f);
		FVector Location = SpawnPoint + FVector(Rand.X, Rand.Y, 0.f);

		TObjectPtr<class AMonsterPawn> SpawnMonster = GetWorld()->SpawnActor<AMonsterPawn>(
			mSpawnClass, Location,	GetActorRotation(), SpawnParams);

		mSpawnMonsters.Add(SpawnMonster);
	}

	++Wave;
}

