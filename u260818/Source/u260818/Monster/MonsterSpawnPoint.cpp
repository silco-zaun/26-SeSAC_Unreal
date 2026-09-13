// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "MonsterBase.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mPatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolPath"));

	mPatrolPath->SetupAttachment(mRoot);

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

	// 배열을 비워준다.
	mPatrolPoints.Empty();

	int32 Count = mPatrolPath->GetNumberOfSplinePoints();

	for (int32 i = 0; i < Count; ++i)
	{
		FVector Point = mPatrolPath->GetLocationAtSplinePoint(i,
			ESplineCoordinateSpace::World);

		mPatrolPoints.Add(Point);
	}
}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawnPoint::ResetSpawn()
{
	if (mSpawnType == EMonsterSpawnType::Once)
	{
		Destroy();
		return;
	}

	if (mSpawnDelay <= 0.f)
		SpawnMonster();
	else
	{
		// 타이머를 생성한다.
		GetWorldTimerManager().SetTimer(mSpawnTimerHandle,
			this, &AMonsterSpawnPoint::SpawnTimerCallback, mSpawnDelay,
			false);
	}
}

void AMonsterSpawnPoint::SpawnTimerCallback()
{
	GetWorldTimerManager().ClearTimer(mSpawnTimerHandle);

	SpawnMonster();
}

void AMonsterSpawnPoint::SpawnMonster()
{
	if (IsValid(mSpawnClass))
	{
		FVector SpawnLocation = GetActorLocation();

		// 생성할 클래스를 이용해서 CDO를 얻어올 수 있다.
		TObjectPtr<AMonsterBase> CDO
			= mSpawnClass->GetDefaultObject<AMonsterBase>();

		if (IsValid(CDO))
		{
			SpawnLocation.Z += CDO->GetCapsule()->GetScaledCapsuleHalfHeight();
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		mSpawnMonster = GetWorld()->SpawnActor<AMonsterBase>(mSpawnClass, SpawnLocation,
			GetActorRotation(), SpawnParams);

		mSpawnMonster->SetSpawnPoint(this);

		// 순찰 경로 전달.
		mSpawnMonster->SetPatrolPoints(mPatrolPoints);
	}
}

