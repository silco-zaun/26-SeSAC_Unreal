// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BillboardWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UBillboardWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UBillboardWidgetComponent(const FObjectInitializer& PCIP);

public:
	virtual void TickComponent(float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};
