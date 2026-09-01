// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AssetSubsystem.generated.h"

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
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

public:
	template <typename T>
	const T* FindPlayerInfo(const FName& Name) const
	{
		if (!IsValid(mPlayerInfoTable))
			return nullptr;

		return
			mPlayerInfoTable->FindRow<FPlayerInfo>(Name, TEXT("FindPlayerInfo"));
	}

public:
	void LoadPlayer();
	void LoadMonster();

public:
	UFUNCTION()
	void PlayerInfoLoadComplete(FPrimaryAssetId LoadId);
};
