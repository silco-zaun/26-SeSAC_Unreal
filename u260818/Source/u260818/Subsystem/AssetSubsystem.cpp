// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetSubsystem.h"
#include "Engine/AssetManager.h"
#include "../Player/PlayerInfoAsset.h"



void UAssetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(Sac8Debug, Warning, TEXT("UAssetSubsystem Initialize"));

	LoadPlayer();
	LoadMonster();
}

void UAssetSubsystem::Deinitialize()
{

}

void UAssetSubsystem::LoadPlayer()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	FPrimaryAssetId AssetId(TEXT("PlayerInfoAsset"), TEXT("DA_PlayerInfo"));

	// AssetId에 해당하는 에셋을 로딩.
	AssetManager.LoadPrimaryAsset(AssetId, TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UAssetSubsystem::PlayerInfoLoadComplete, AssetId));
}

void UAssetSubsystem::LoadMonster()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	FPrimaryAssetId AssetId(TEXT("PlayerInfoAsset"), TEXT("DA_MonsterInfo"));

	// AssetId에 해당하는 에셋을 로딩.
	AssetManager.LoadPrimaryAsset(AssetId, TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UAssetSubsystem::MonsterInfoLoadComplete, AssetId));
}

void UAssetSubsystem::PlayerInfoLoadComplete(FPrimaryAssetId LoadId)
{
	// 로딩된 오브젝트를 얻어온다.
	TObjectPtr<UObject> LoadedObject = UAssetManager::Get().GetPrimaryAssetObject(LoadId);

	TObjectPtr<UPlayerInfoAsset> DataAsset =
		Cast<UPlayerInfoAsset>(LoadedObject);

	if (IsValid(DataAsset))
	{
		// 비동기 로드 처리.
		mPlayerInfoTable = DataAsset->mPlayerInfoDataTable.LoadSynchronous();
		mLoadPlayerInfo = true;

		// 델리게이트에 등록된 함수가 있을 경우
		if (mOnPlayerDataLoading.IsBound())
		{
			// 등록된 모든 함수를 호출한다.
			mOnPlayerDataLoading.Broadcast();
		}
	}
}

void UAssetSubsystem::MonsterInfoLoadComplete(FPrimaryAssetId LoadId)
{
	UE_LOG(Sac8Debug, Warning, TEXT("MonsterInfoLoadComplete"));

	// 로딩된 오브젝트를 얻어온다.
	TObjectPtr<UObject> LoadedObject = UAssetManager::Get().GetPrimaryAssetObject(LoadId);

	TObjectPtr<UPlayerInfoAsset> DataAsset =
		Cast<UPlayerInfoAsset>(LoadedObject);

	if (IsValid(DataAsset))
	{
		// 비동기 로드 처리.
		mMonsterInfoTable = DataAsset->mPlayerInfoDataTable.LoadSynchronous();
		mLoadMonsterInfo = true;

		// 델리게이트에 등록된 함수가 있을 경우
		if (mOnMonsterDataLoading.IsBound())
		{
			// 등록된 모든 함수를 호출한다.
			mOnMonsterDataLoading.Broadcast();
		}
	}
}
