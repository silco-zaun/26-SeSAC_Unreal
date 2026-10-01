// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterialBase.h"

UPhysicalMaterialBase::UPhysicalMaterialBase(FVTableHelper& Helper) :
	Super(Helper)
{
}

void UPhysicalMaterialBase::PostLoad()
{
	Super::PostLoad();
}

void UPhysicalMaterialBase::FinishDestroy()
{
	Super::FinishDestroy();
}
