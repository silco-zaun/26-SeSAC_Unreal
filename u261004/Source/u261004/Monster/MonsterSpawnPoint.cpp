// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "MonsterPawn.h"
#include "../Subsystem/UISubsystem.h"
#include "../UI/Main/MainWidget.h"

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

void AMonsterSpawnPoint::SpawnTimerCallback()
{
	GetWorldTimerManager().ClearTimer(mSpawnTimerHandle);

	if (mWave < 1)
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid Wave"));
		return;
	}

	if (mWave > 3)
	{
		UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

		if (Subsystem)
		{
			UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

			if (MainWidget)
			{
				MainWidget->SetResultText(TEXT("승리"));
			}
		}

		return;
	}

	SpawnMonster();
}

void AMonsterSpawnPoint::SpawnMonster()
{
	if (!IsValid(mSpawnClass))
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid SpawnClass"));
		return;
	}

	if (mWave < 1 || mWave > 3)
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid Wave"));
		return;
	}

	FVector SpawnPoint = GetActorLocation();

	// 생성할 클래스를 이용해서 CDO를 얻어올 수 있다.
	TObjectPtr<AMonsterPawn> MonsterCDO =
		mSpawnClass->GetDefaultObject<AMonsterPawn>();

	if (IsValid(MonsterCDO))
		SpawnPoint.Z += MonsterCDO->GetCapsule()->GetScaledCapsuleHalfHeight();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < mWave * 5; ++i)
	{
		FVector2D Rand = FMath::RandPointInCircle(2000.f);
		FVector Location = SpawnPoint + FVector(Rand.X, Rand.Y, 0.f);

		TObjectPtr<class AMonsterPawn> SpawnMonster = GetWorld()->SpawnActor<AMonsterPawn>(
			mSpawnClass, Location,	GetActorRotation(), SpawnParams);

		SpawnMonster->AddMonsterDeathCallback<AMonsterSpawnPoint>(this, &AMonsterSpawnPoint::MonsterChange);

		mSpawnMonsters.Add(SpawnMonster);
	}

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

		if (MainWidget)
		{
			MainWidget->SetWaveText(FString::Printf(TEXT("Wave : %d"), mWave));
			MainWidget->SetMonsterText(FString::Printf(TEXT("Monster : %d"), mSpawnMonsters.Num()));
		}
	}

	// 타이머를 생성한다.
	GetWorldTimerManager().SetTimer(mSpawnTimerHandle,
		this, &AMonsterSpawnPoint::SpawnTimerCallback, mSpawnDelay,
		false);

	mWave++;
}

void AMonsterSpawnPoint::MonsterChange()
{
	//UE_LOG(LogTestDebug, Warning, TEXT("몬스터 갱신"));

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

		if (MainWidget)
		{
			int32 MonsterNum = 0;

			for (TObjectPtr<class AMonsterPawn> Monster : mSpawnMonsters)
			{
				if (IsValid(Monster))
				{
					MonsterNum++;
				}
			}

			MainWidget->SetMonsterText(FString::Printf(TEXT("Monster : %d"), MonsterNum));
		}
	}
}
