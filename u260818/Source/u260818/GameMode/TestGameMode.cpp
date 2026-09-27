// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"
#include "../Player/Wukong.h"
#include "../Player/Wraith/Wraith.h"
#include "../Player/MainPlayerState.h"
#include "../Player/MainPlayerController.h"

ATestGameMode::ATestGameMode()
{
	DefaultPawnClass = AWukong::StaticClass();
	PlayerStateClass = AMainPlayerState::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

APlayerController* ATestGameMode::Login(UPlayer* NewPlayer,
	ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	APlayerController* Result = Super::Login(NewPlayer, InRemoteRole,
		Portal, Options, UniqueId, ErrorMessage);

	int32 Job = 0;
	FParse::Value(*Options, TEXT("Job="), Job);

	switch ((EPlayerJob)Job)
	{
	case EPlayerJob::Knight:
		DefaultPawnClass = AWukong::StaticClass();
		break;
	case EPlayerJob::Archer:
		break;
	case EPlayerJob::Wizard:
		break;
	case EPlayerJob::Gunner:
		DefaultPawnClass = AWraith::StaticClass();
		break;
	}

	FString PlayerName;
	FParse::Value(*Options, TEXT("PlayerName="), PlayerName);

	AMainPlayerController* Controller =
		Cast<AMainPlayerController>(Result);

	if (IsValid(Controller))
		Controller->SetPlayerName(PlayerName);

	return Result;
}

void ATestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AMainPlayerController* Controller =
		Cast<AMainPlayerController>(NewPlayer);

	if (IsValid(Controller))
	{
		AMainPlayerState* State = Cast<AMainPlayerState>(Controller->PlayerState);

		if (IsValid(State))
		{
			State->SetPlayerName(Controller->GetPlayerName());

			UE_LOG(Sac8Debug, Warning, TEXT("Name = %s"),
				*Controller->GetPlayerName());
		}
	}
}
