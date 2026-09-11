// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	UItemObject();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemTableInfo mItemInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mUpgrade = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mCount = 1;

public:
	const FItemTableInfo& GetItemInfo() const
	{
		return mItemInfo;
	}

	int32 GetItemUpgrade() const
	{
		return mUpgrade;
	}

	int32 GetItemCount() const
	{
		return mCount;
	}

public:
	void SetItemInfo(const FItemTableInfo& Info)
	{
		mItemInfo = Info;
	}

	void SetItemUpgrade(int32 Upgrade)
	{
		mUpgrade = Upgrade;
	}

	void AddItemUpgrade(int32 Upgrade = 1)
	{
		mUpgrade += Upgrade;
	}

	void SetItemCount(int32 Count)
	{
		mCount = Count;
	}

	void AddItemCount(int32 Count = 1)
	{
		mCount += Count;
	}
};
