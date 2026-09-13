// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UI/BaseWidget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	TMap<FString, TObjectPtr<UBaseWidget>> mWidgetMap;

public:
	void AddWidget(const FString& Name, UBaseWidget* Widget);
	void RemoveWidget(const FString& Name);
	template <typename T>
	T* FindWidget(const FString& Name)
	{
		return Cast<T>(mWidgetMap.FindRef(Name));
	}
};
