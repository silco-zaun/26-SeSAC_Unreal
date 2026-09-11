// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U260818_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<class UItemObject>> mItemList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 mItemCount = 0;

public:
	int32 GetItemCount() const
	{
		return mItemCount;
	}

	int32 GetInventoryMaxCount() const
	{
		return mItemList.Num();
	}

	class UItemObject* GetItem(int32 Index)
	{
		return mItemList[Index];
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent();

public:
	bool AddItem(const FItemTableInfo& ItemInfo);
};
