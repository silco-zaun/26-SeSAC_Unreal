// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include <InputAction.h>
#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>
#include "UObject/Object.h"
#include "Input.generated.h"

UCLASS()
class U260818_API UInput : public UObject
{
	GENERATED_BODY()

public:
	UInput();

public:
	TObjectPtr<UInputMappingContext> mContext;
	
protected:
	// FString : 언리얼엔진에서 제공해주는 문자열 클래스이다.
	TMap<FString, TObjectPtr<UInputAction>> mActions;

public:
	TObjectPtr<UInputAction> FindAction(const FString& Name) const;
};

UCLASS()
class U260818_API UTestInput : public UInput
{
	GENERATED_BODY()

public:
	UTestInput();
};