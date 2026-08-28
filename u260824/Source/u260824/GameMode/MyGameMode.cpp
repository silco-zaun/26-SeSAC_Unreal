// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "../Player/Riktor.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = ARiktor::StaticClass();
}
