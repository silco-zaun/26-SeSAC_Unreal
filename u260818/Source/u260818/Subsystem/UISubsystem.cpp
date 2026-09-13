// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubsystem.h"

void UUISubsystem::AddWidget(const FString& Name, UBaseWidget* Widget)
{
	// Contains 함수를 이용해서 같은 키가 있는지 판단한다.
	if (mWidgetMap.Contains(Name))
	{
		UE_LOG(Sac8Debug, Warning, 
			TEXT("This widget already contained : %s"),
			*Name);
		return;
	}

	mWidgetMap.Add(Name, Widget);
}

void UUISubsystem::RemoveWidget(const FString& Name)
{
	// Contains 함수를 이용해서 같은 키가 있는지 판단한다.
	if (!mWidgetMap.Contains(Name))
		return;

	mWidgetMap.Remove(Name);
}
