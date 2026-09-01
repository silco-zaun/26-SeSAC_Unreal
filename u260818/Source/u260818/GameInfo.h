#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "GameInfo.generated.h"

// 로그 카테고리 선언.
DECLARE_LOG_CATEGORY_EXTERN(Sac8Debug, Warning, All);

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
	EPlayerJob Job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float HPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	int32 Gold;

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
	EMonsterType MonsterType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterInfo")
	int32 Gold;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TMap<FString, TObjectPtr<UAnimSequenceBase>>	Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
	TObjectPtr<USkeletalMesh> BodyMesh;
};
