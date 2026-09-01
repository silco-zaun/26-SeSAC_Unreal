// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetSubsystem.h"
#include "Engine/AssetManager.h"
#include "../Player/PlayerInfoAsset.h"



void UAssetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	LoadPlayer();
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
	}
}
