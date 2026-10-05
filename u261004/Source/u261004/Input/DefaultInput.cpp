// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultInput.h"

UDefaultInput::UDefaultInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContext(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));

	if (InputMappingContext.Succeeded())
		mInputMappingContext = InputMappingContext.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveInputAction(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));

	if (MoveInputAction.Succeeded())
		mInputActionMap.Add(TEXT("Move"), MoveInputAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction> LookInputAction(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Look.IA_Look'"));

	if (LookInputAction.Succeeded())
		mInputActionMap.Add(TEXT("Look"), LookInputAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpInputAction(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));

	if (JumpInputAction.Succeeded())
		mInputActionMap.Add(TEXT("Jump"), JumpInputAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackInputAction(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Attack.IA_Attack'"));

	if (AttackInputAction.Succeeded())
		mInputActionMap.Add(TEXT("Attack"), AttackInputAction.Object);
}
