// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

AMainPlayerState::AMainPlayerState()
{
	UE_LOG(LogTestOrder, Warning, TEXT("AMainPlayerState::Constructor - %s"), *GetName());
}
