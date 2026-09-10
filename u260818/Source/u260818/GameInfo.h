#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"

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

FRotator GetTargetRotation(const FVector& Target,
	const FVector& Self);
FRotator GetTargetRotationYaw(FVector Target,
	FVector Self);
bool GetRandomNavigationPoint(FVector& Result, UWorld* World,
	const FVector& Center, float Radius);

#define TeamNeutral 255
#define TeamPlayer 10
#define TeamMonster 20

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Armor,
	Potion
};

UENUM(BlueprintType)
enum class EItemUILayerType : uint8
{
	Single,
	Layered
};

UENUM(BlueprintType)
enum class EItemOptionType : uint8
{
	Attack,
	Defense,
	HPMax,
	MPMax,
	HPRecovery,
	MPRecovery,
	MoveSpeed,
	AttackSpeed,
	AttackDistance,
	CriticalRatio,
	CriticalDamage
};

USTRUCT(BlueprintType)
struct FItemOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemOptionType Type;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Option;
};

// 데이터테이블용 구조체는 반드시 FTableRowBase를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FItemTableInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemUILayerType UILayerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FString Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 PurchasePrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	TObjectPtr<UTexture2D> IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	TObjectPtr<USkeletalMesh> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	TArray<FItemOption> Option;
};

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

USTRUCT(BlueprintType)
struct FDropItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FString ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Percent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropItem")
	TArray<FDropItemInfo> DropItems;
};

UENUM(BlueprintType)
enum class EMonsterNormalAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	End
};
