// Fill out your copyright notice in the Description page of Project Settings.


#include "Input.h"

UInput::UInput()
{
}

TObjectPtr<UInputAction> UInput::FindAction(const FString& Name) const
{
	return mActions.FindRef(Name);
}



UTestInput::UTestInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Test.IMC_Test'"));

	if (IMC.Succeeded())
		mContext = IMC.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		MoveAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));

	if (MoveAction.Succeeded())
		mActions.Add(TEXT("Move"), MoveAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction>
		RotCharAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Rotation_Character.IA_Rotation_Character'"));

	if (RotCharAction.Succeeded())
		mActions.Add(TEXT("RotChar"), RotCharAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction>
		RotCameraAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Rotation_Camera.IA_Rotation_Camera'"));

	if (RotCameraAction.Succeeded())
		mActions.Add(TEXT("RotCamera"), RotCameraAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction>
		CameraZoomAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Camera_Zoom.IA_Camera_Zoom'"));

	if (CameraZoomAction.Succeeded())
		mActions.Add(TEXT("CameraZoom"), CameraZoomAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction>
		JumpAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));

	if (JumpAction.Succeeded())
		mActions.Add(TEXT("Jump"), JumpAction.Object);

	static ConstructorHelpers::FObjectFinder<UInputAction>
		AttackAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Attack.IA_Attack'"));

	if (AttackAction.Succeeded())
		mActions.Add(TEXT("Attack"), AttackAction.Object);
}
