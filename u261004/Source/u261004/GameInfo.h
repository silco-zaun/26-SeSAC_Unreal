#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

#include "GameInfo.generated.h"

// 로그 카테고리 선언
DECLARE_LOG_CATEGORY_EXTERN(LogTestDebug, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTestOrder, Log, All);

FRotator GetTargetRotation(const FVector& Target,
	const FVector& Self);
FRotator GetTargetRotationYaw(FVector Target,
	FVector Self);

#define TeamNeutral 255
#define TeamPlayer 10
#define TeamMonster 20

DECLARE_MULTICAST_DELEGATE_TwoParams(FHPChange, float, float);
DECLARE_MULTICAST_DELEGATE(FMonsterDeath);

// 데이터테이블용 구조체는 반드시 FTableRowBase를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Attack = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Defense = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HPMax = 100.0f;
};

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Run,
	Attack,
	Death,
	End
};

// 데이터테이블용 구조체는 반드시 FTableRowBase를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Attack = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Defense = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float HP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float HPMax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TObjectPtr<USkeletalMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TMap<FString, TObjectPtr<UAnimSequenceBase>> Anim;
};
