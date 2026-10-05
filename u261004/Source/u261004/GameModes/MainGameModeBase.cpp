// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../Player/Crunch/Crunch.h"
#include "../Player/MainPlayerController.h"
#include "../Player/MainPlayerState.h"

AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = ACrunch::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMainPlayerState::StaticClass();
}
