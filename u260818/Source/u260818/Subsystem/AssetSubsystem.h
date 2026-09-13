// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AssetSubsystem.generated.h"

// Delegate를 생성하면 Delegate를 사용할 수 있는 타입이 만들어진다.
DECLARE_MULTICAST_DELEGATE(FOnDataLoading);

/**
 * 
 */
UCLASS()
class U260818_API UAssetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	TObjectPtr<UDataTable> mPlayerInfoTable;
	TObjectPtr<UDataTable> mMonsterInfoTable;
	TObjectPtr<UDataTable> mItemInfoTable;
	FOnDataLoading mOnPlayerDataLoading;
	FOnDataLoading mOnMonsterDataLoading;
	FOnDataLoading mOnItemDataLoading;
	bool mLoadPlayerInfo = false;
	bool mLoadMonsterInfo = false;
	bool mLoadItemInfo = false;

public:
	bool GetLoadPlayerInfo()	const
	{
		return mLoadPlayerInfo;
	}

	bool GetLoadMonsterInfo()	const
	{
		return mLoadMonsterInfo;
	}

	bool GetLoadItemInfo() const
	{
		return mLoadItemInfo;
	}

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

public:
	const FPlayerInfo* FindPlayerInfo(const FName& Name) const
	{
		if (!IsValid(mPlayerInfoTable))
			return nullptr;

		return mPlayerInfoTable->FindRow<FPlayerInfo>(Name, TEXT("FindPlayerInfo"));
	}

	const FMonsterInfo* FindMonsterInfo(const FName& Name) const
	{
		if (!IsValid(mMonsterInfoTable))
			return nullptr;

		return mMonsterInfoTable->FindRow<FMonsterInfo>(Name, TEXT("FindMonsterInfo"));
	}

	const FItemTableInfo* FindItemInfo(const FName& Name) const
	{
		if (!IsValid(mItemInfoTable))
			return nullptr;

		return mItemInfoTable->FindRow<FItemTableInfo>(Name, TEXT("FindItem"));
	}

public:
	void LoadPlayer();
	void LoadMonster();
	void LoadItem();

public:
	UFUNCTION()
	void PlayerInfoLoadComplete(FPrimaryAssetId LoadId);

	UFUNCTION()
	void MonsterInfoLoadComplete(FPrimaryAssetId LoadId);

	UFUNCTION()
	void ItemInfoLoadComplete(FPrimaryAssetId LoadId);

public:
	template <typename T>
	void AddDataAssetLoadingDelegate(T* Obj, void (T::* Func)())
	{
		mOnPlayerDataLoading.AddUObject(Obj, Func);
	}

	template <typename T>
	void AddMonsterDataAssetLoadingDelegate(T* Obj, void (T::* Func)())
	{
		mOnMonsterDataLoading.AddUObject(Obj, Func);
	}

	template <typename T>
	void AddItemDataAssetLoadingDelegate(T* Obj, void (T::* Func)())
	{
		mOnItemDataLoading.AddUObject(Obj, Func);
	}
};
