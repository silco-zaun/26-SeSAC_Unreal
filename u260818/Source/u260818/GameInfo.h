#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

#include "GameInfo.generated.h"

// 로그 카테고리 선언.
DECLARE_LOG_CATEGORY_EXTERN(Sac8Debug, Warning, All);

#define TeamNeutral 255
#define TeamPlayer 10
#define TeamMonster 20

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	Knight,
	Archer,
	Wizard,
	Gunner
};

// 데이터테이블용 구조체는 반드시 FTableRowBase를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	FString PlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	EPlayerJob Job = EPlayerJob::Knight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Attack = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Defense = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HP = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HPMax = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MP = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MPMax = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MoveSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float AttackDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Exp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemMesh")
	TMap<FString, TObjectPtr<USkeletalMesh>>	ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemMesh")
	TMap<FString, TObjectPtr<UAnimSequenceBase>>	Animation;
};

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	Normal,
	Epic,
	Legendary
};

// 데이터테이블용 구조체는 반드시 FTableRowBase를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	FString MonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	EMonsterType MonsterType = EMonsterType::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Attack = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Defense = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float HP = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float MP = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float MoveSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float AttackDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float DetectRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Exp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Gold = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TMap<FString, TObjectPtr<UAnimSequenceBase>>	Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TObjectPtr<USkeletalMesh> BodyMesh;
};
