// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetSubsystem.h"
#include "Engine/AssetManager.h"
#include "../Data/MainPrimaryDataAsset.h"

void UAssetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTestOrder, Log, TEXT("UAssetSubsystem::Initialize"));

	LoadPlayerInfo();
	LoadMonsterInfo();
}

void UAssetSubsystem::Deinitialize()
{
}

void UAssetSubsystem::LoadPlayerInfo()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	FPrimaryAssetId AssetId(TEXT("MainPrimaryDataAsset"), TEXT("DA_PlayerInfo"));

	// AssetId에 해당하는 에셋을 로딩
	AssetManager.LoadPrimaryAsset(AssetId, TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UAssetSubsystem::PlayerInfoLoadComplete, AssetId));
}

void UAssetSubsystem::LoadMonsterInfo()
{
	UAssetManager& AssetManager = UAssetManager::Get();

	FPrimaryAssetId AssetId(TEXT("MainPrimaryDataAsset"), TEXT("DA_MonsterInfo"));

	// AssetId에 해당하는 에셋을 로딩.
	AssetManager.LoadPrimaryAsset(AssetId, TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UAssetSubsystem::MonsterInfoLoadComplete, AssetId));
}

void UAssetSubsystem::PlayerInfoLoadComplete(FPrimaryAssetId LoadId)
{
	UE_LOG(LogTestOrder, Log, TEXT("UAssetSubsystem::PlayerInfoLoadComplete"));

	// 로딩된 오브젝트를 얻어온다.
	TObjectPtr<UObject> LoadedObject = 
		UAssetManager::Get().GetPrimaryAssetObject(LoadId);

	TObjectPtr<UMainPrimaryDataAsset> DataAsset =
		Cast<UMainPrimaryDataAsset>(LoadedObject);

	if (IsValid(DataAsset))
	{
		// 비동기 로드 처리.
		mPlayerInfoTable = DataAsset->mDataTable.LoadSynchronous();
		mIsPlayerInfoLoadComplete = true;

		// 델리게이트에 등록된 함수가 있을 경우
		if (mOnPlayerInfoLoadComplete.IsBound())
		{
			// 등록된 모든 함수를 호출한다.
			mOnPlayerInfoLoadComplete.Broadcast();
		}
	}
}

void UAssetSubsystem::MonsterInfoLoadComplete(FPrimaryAssetId LoadId)
{
	UE_LOG(LogTestOrder, Log, TEXT("UAssetSubsystem::MonsterInfoLoadComplete"));

	// 로딩된 오브젝트를 얻어온다.
	TObjectPtr<UObject> LoadedObject = 
		UAssetManager::Get().GetPrimaryAssetObject(LoadId);

	TObjectPtr<UMainPrimaryDataAsset> DataAsset =
		Cast<UMainPrimaryDataAsset>(LoadedObject);

	if (IsValid(DataAsset))
	{
		// 비동기 로드 처리.
		mMonsterInfoTable = DataAsset->mDataTable.LoadSynchronous();
		mIsMonsterInfoLoadComplete = true;

		// 델리게이트에 등록된 함수가 있을 경우
		if (mOnMonsterInfoLoadComplete.IsBound())
		{
			// 등록된 모든 함수를 호출한다.
			mOnMonsterInfoLoadComplete.Broadcast();
		}
	}


}
