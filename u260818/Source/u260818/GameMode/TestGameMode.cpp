// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"
#include "../Player/Wukong.h"
#include "../Player/MainPlayerState.h"
#include "../Player/MainPlayerController.h"

ATestGameMode::ATestGameMode()
{
	DefaultPawnClass = AWukong::StaticClass();
	PlayerStateClass = AMainPlayerState::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}
