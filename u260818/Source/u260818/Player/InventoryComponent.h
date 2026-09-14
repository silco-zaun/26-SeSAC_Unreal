// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryItemChange, class UItemObject*, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FInventoryItemCountChange, int32, int32);

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

protected:
	FInventoryItemChange mItemChangeDelegate;
	FInventoryItemCountChange mItemCountChangeDelegate;

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
	void SwapItem(int32 StartIndex, int32 EndIndex);
	bool UseItem(int32 Index);

public:
	UFUNCTION()
	void ItemInfoLoadComplete();

private:
	void UsePotion(int32 Index);
	void UseWeapon(int32 Index);
	void UseArmor(int32 Index);

public:
	template <typename T>
	void AddItemChangeCallback(T* Obj, void (T::* Func)(class UItemObject*, int32))
	{
		mItemChangeDelegate.AddUObject(Obj, Func);
	}

	template <typename T>
	void AddItemCountChangeCallback(T* Obj, void (T::* Func)(class UItemObject*, int32))
	{
		mItemChangeDelegate.AddUObject(Obj, Func);
	}

	template <typename T>
	void AddItemCountChangeCallback(T* Obj, void (T::* Func)(int32, int32))
	{
		mItemCountChangeDelegate.AddUObject(Obj, Func);
	}
};
