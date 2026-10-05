// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AssetSubsystem.generated.h"

// Delegate를 생성하면 Delegate를 사용할 수 있는 타입이 만들어진다.
DECLARE_MULTICAST_DELEGATE(FOnDataAssetLoadComplete);

/**
 * 
 */
UCLASS()
class U261004_API UAssetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TObjectPtr<UDataTable> mPlayerInfoTable;
	TObjectPtr<UDataTable> mMonsterInfoTable;
	FOnDataAssetLoadComplete mOnPlayerInfoLoadComplete;
	FOnDataAssetLoadComplete mOnMonsterInfoLoadComplete;
	bool mIsPlayerInfoLoadComplete = false;
	bool mIsMonsterInfoLoadComplete = false;

public:
	bool GetIsPlayerInfoLoadComplelte() const
	{
		return mIsPlayerInfoLoadComplete;
	}

	bool GetIsMonsterInfoLoadComplelte() const
	{
		return mIsMonsterInfoLoadComplete;
	}

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	const FPlayerInfo* FindPlayerInfo(const FName& Name) const
	{
		if (IsValid(mPlayerInfoTable))
		{
			return mPlayerInfoTable->FindRow<FPlayerInfo>(Name, TEXT("FindPlayerInfo"));
		}

		return nullptr;
	}

	const FMonsterInfo* FindMonsterInfo(const FName& Name) const
	{
		if (IsValid(mMonsterInfoTable))
		{
			return mMonsterInfoTable->FindRow<FMonsterInfo>(Name, TEXT("FindMonsterInfo"));
		}

		return nullptr;
	}

private:
	void LoadPlayerInfo();
	void LoadMonsterInfo();

private:
	UFUNCTION()
	void PlayerInfoLoadComplete(FPrimaryAssetId LoadId);

	UFUNCTION()
	void MonsterInfoLoadComplete(FPrimaryAssetId LoadId);

public:
	template <typename T>
	void AddPlayerInfoLoadCompleteDelegate(T* Obj, void (T::* Func)())
	{
		mOnPlayerInfoLoadComplete.AddUObject(Obj, Func);
	}

	template <typename T>
	void AddMonsterInfoLoadCompleteDelegate(T* Obj, void (T::* Func)())
	{
		mOnMonsterInfoLoadComplete.AddUObject(Obj, Func);
	}
};
