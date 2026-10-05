// Fill out your copyright notice in the Description page of Project Settings.


#include "Input.h"

UInput::UInput()
{
}

TObjectPtr<UInputAction> UInput::FindInputAction(const FString& Name) const
{
	return mInputActionMap.FindRef(Name);
}
