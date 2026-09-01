// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "MainPlayerState.h"
#include "../Subsystem/AssetSubsystem.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mArm = CreateDefaultSubobject<USpringArmComponent>(
		TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(
		TEXT("Camera"));

	mArm->SetupAttachment(GetMesh());
	mCamera->SetupAttachment(mArm);

	mArm->TargetArmLength = 500.f;
	//mArm->bUsePawnControlRotation = true;

	// 충돌 설정
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
// 빙의된 후에 BeginPlay가 호출된다.
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSystem)
	{
		//const FPlayerInfo* Info = AssetSystem->FindPlayerInfo<FPlayerInfo>(mInfoName);
	}
	
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// InputMappingContext를 지정한다.
	// PlayerController를 얻어온다.
	// Pawn종류는 자신에게 빙의된 컨트롤러를 반환하는 기능을 제공한다.
	// 언리얼엔진에서는 Cast 함수를 이용해서 UObject에 대한 형변환을
	// 진행한다.
	TObjectPtr<APlayerController> PlayerController =
		Cast<APlayerController>(GetController());
	//GetController<APlayerController>();

	// UObject타입 객체가 유효한 객체인지를 체크한다.
	if (IsValid(PlayerController))
	{
		// PlayerController가 가지고 있는 InputSystem을 얻어온다.
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer());

		// InputMappingContext를 가지고 있는 CDO를 얻어온다.
		const UTestInput* InputCDO = GetDefault<UTestInput>();

		// InputMappingContext를 InputSystem에 등록한다.
		InputSystem->AddMappingContext(InputCDO->mContext, 0);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// InputComponent에 InputAction을 등록하고 해당 InputAction이 동작될때
	// 호출할 함수를 등록한다.
	// UInputComponent 타입을 UEnhancedInputComponent 타입으로 변환한다.
	TObjectPtr<UEnhancedInputComponent> Input =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(Input))
	{
		// InputAction을 가지고 있는 CDO를 얻어온다.
		const UTestInput* InputCDO = GetDefault<UTestInput>();

		// 1번인자 : 바인딩할 InputAction을 지정한다
		// 2번인자 : 이 Action에 저장된 Key가 어떻게 반응할지 지정한다.
		// 3번인자 : 이 Action이 동작할 때 호출할 함수를 가지고 있는 UObject
		// 객체를 지정한다.
		// 4번인자 : 이 Action이 동작할 떄 호출할 함수의 주소를 등록한다.
		Input->BindAction(InputCDO->FindAction(TEXT("Move")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::MoveKey);

		Input->BindAction(InputCDO->FindAction(TEXT("RotChar")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::RotationCharacterKey);

		Input->BindAction(InputCDO->FindAction(TEXT("RotCamera")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::RotationCameraKey);

		Input->BindAction(InputCDO->FindAction(TEXT("CameraZoom")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::CameraZoomKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Jump")),
			ETriggerEvent::Started, this, &APlayerCharacter::JumpKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Attack")),
			ETriggerEvent::Started, this, &APlayerCharacter::AttackKey);

		Input->BindAction(InputCDO->FindAction(TEXT("HitTest")),
			ETriggerEvent::Started, this, &APlayerCharacter::HitKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill1")),
			ETriggerEvent::Started, this, &APlayerCharacter::Skill1Key);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill1")),
			ETriggerEvent::Completed, this, &APlayerCharacter::Skill1ReleaseKey);
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, 
	struct FDamageEvent const& DamageEvent, class AController* EventInstigator, 
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	UE_LOG(Sac8Debug, Warning, TEXT("Damage : %.2f"), DamageAmount);

	return DamageAmount;
}

void APlayerCharacter::MoveKey(const FInputActionValue& Value)
{
	//UE_LOG(Sac8Debug, Warning, TEXT("MoveKey"));

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
	//	TEXT("MoveKey"));
	FVector2D Axis = Value.Get<FVector2D>();

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();

	FVector MoveDir = Forward * Axis.X + Right * Axis.Y;

	MoveDir.Normalize();

	AddMovementInput(MoveDir, 1.f);

	// 전방 방향으로 이동
	//AddMovementInput(GetActorForwardVector(), Axis.X);

	// 오른쪽 방향으로 이동
	//AddMovementInput(GetActorRightVector(), Axis.Y);

	//UE_LOG(Sac8Debug, Warning, TEXT("X : %.5f, Y : %.5f"), Axis.X, Axis.Y);
}

void APlayerCharacter::RotationCharacterKey(const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();

	AddControllerYawInput(Axis);
}

/*
1. 회전키 Action을 하나 더 만든다.
2. 마우스를 왼쪽, 오른쪽으로 움직이거나 위, 아래로 움직일 때 반응한다.
3. 마우스를 왼쪽, 오른쪽으로 움직일 때 SpringArm을 회전시킨다.
*/
void APlayerCharacter::RotationCameraKey(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();

	mArm->AddRelativeRotation(FRotator(Axis.X, Axis.Y, 0.0));

	mAnimInst->AddViewYaw(Axis.Y);
	mAnimInst->AddViewPitch(Axis.X);

	//UE_LOG(Sac8Debug, Warning, TEXT("X : %.5f, Y : %.5f"), Axis.X, Axis.Y);
}

void APlayerCharacter::CameraZoomKey(const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();

	mArm->TargetArmLength -= Axis * 30.f;

	if (mArm->TargetArmLength < 150.f)
		mArm->TargetArmLength = 150.f;
	else if (mArm->TargetArmLength > 500.f)
		mArm->TargetArmLength = 500.f;

	//UE_LOG(Sac8Debug, Warning, TEXT("Wheel : %.5f"), Axis);
}

void APlayerCharacter::JumpKey(const FInputActionValue& Value)
{
	// 점프가 가능한 상태일 경우 점프한다.
	// 땅에 닿으면 CanJump == true 가 된다.
	if (CanJump())
		Jump();
}

void APlayerCharacter::AttackKey(const FInputActionValue& Value)
{
	mAnimInst->PlayAttack();
}

void APlayerCharacter::HitKey(const FInputActionValue& Value)
{
	mAnimInst->PlayHit();

	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();

	if (IsValid(State))
	{
		State->AddHP(-100.f);

		UE_LOG(Sac8Debug, Warning, TEXT("HP : %.2f"),
			State->GetHP());

		if (State->GetHP() == 0.f)
		{
			mAnimInst->Death();
		}
		else
		{
			mAnimInst->PlayHit();
		}
	}
}

void APlayerCharacter::Skill1Key(const FInputActionValue& Value)
{
	UE_LOG(Sac8Debug, Warning, TEXT("Skill1Key"));
	Skill1();
}

void APlayerCharacter::Skill1ReleaseKey(const FInputActionValue& Value)
{
	UE_LOG(Sac8Debug, Warning, TEXT("Skill1ReleaseKey"));
	Skill1Release();
}

void APlayerCharacter::Attack()
{

}

void APlayerCharacter::Death()
{

}

void APlayerCharacter::Skill1()
{
}

void APlayerCharacter::Skill1Release()
{
}
