// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "MainPlayerState.h"
#include "../Input/DefaultInput.h"
#include "../Subsystem/AssetSubsystem.h"
#include "../Subsystem/UISubsystem.h"
#include "../UI/Main/MainWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	UE_LOG(LogTestOrder, Log, TEXT("APlayerCharacter::Constructor - %s"), *GetName());

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//mHPBarBillboardWidgetComponent = CreateDefaultSubobject<UBillboardWidgetComponent>(TEXT("HPBarBillboardWidgetComponent"));

	mArm->SetupAttachment(GetMesh());
	mCamera->SetupAttachment(mArm);
	mArm->TargetArmLength = 500.f;
	mArm->bUsePawnControlRotation = true;
	//mHPBarBillboardWidgetComponent->SetupAttachment(GetMesh(), TEXT("HealthBar"));

	// 선택1. 마우스를 돌리면 캐릭터 몸도 즉시 같이 돎(FPS / TPS 슈터 스타일)
	//bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	// 선택2. 카메라만 자유롭게 돌고, 캐릭터는 이동하는 방향으로 부드럽게 돎 (액션 RPG 스타일)
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 충돌 설정
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	SetGenericTeamId(FGenericTeamId(TeamNeutral));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTestOrder, Warning,
		TEXT("APlayerCharacter::BeginPlay - %s / Controller : %s / PlayerState : %s"),
		*GetName(),
		IsValid(GetController()) ? *GetController()->GetName() : TEXT("null"),
		IsValid(GetPlayerState<AMainPlayerState>()) ? TEXT("Valid") : TEXT("null"));

	UAssetSubsystem* AssetSubsystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSubsystem)
	{
		if (AssetSubsystem->GetIsPlayerInfoLoadComplelte())
		{
			InfoLoadComplete();
		}
		else
		{
			AssetSubsystem->AddPlayerInfoLoadCompleteDelegate(this, &APlayerCharacter::InfoLoadComplete);
		}
	}

	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// InputMappingContext를 지정한다.
	// PlayerController를 얻어온다.
	// Pawn종류는 자신에게 빙의된 컨트롤러를 반환하는 기능을 제공한다.
	// 언리얼엔진에서는 Cast 함수를 이용해서 UObject에 대한 형변환을
	// 진행한다.
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController());

	// UObject타입 객체가 유효한 객체인지를 체크한다.
	if (IsValid(PlayerController))
	{
		// PlayerController가 가지고 있는 InputSystem을 언어온다.
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer());

		// InputMappingContext를 가지고 있는 CDO를 얻어온다.
		const UDefaultInput* DefaultInputCDO = GetDefault<UDefaultInput>();

		// InputMappingContext를 InputSystem에 등록한다.
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputCDO->mInputMappingContext, 0);
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

	// InputConponent에 InputAction을 등록하고 해당 inputAction이 동작될때
	// 호출할 함수를 등록한다.
	// UInputComponent 타입을 UEnhancedInputComponent 타입으로 변환한다.
	TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(PlayerEnhancedInputComponent))
	{
		// InputAction을 가지고 있는 CDO를 얻어온다.
		const UDefaultInput* DefaultInputCDO = GetDefault<UDefaultInput>();

		// 1번인자 : 바인딩할 InputAction을 지정한다.
		// 2번인자 : 이 Action에 저장된 Key가 어떻게 반응할지 지정한다.
		// 3번인자 : 이 Action이 동작할 때 호출할 함수를 가지고 있는 UObject
		// 객체를 지정한다.
		// 4번인자 : 이 Action이 동작할 때 호출할 함수의 주소를 등록한다.
		PlayerEnhancedInputComponent->BindAction(DefaultInputCDO->FindInputAction(TEXT("Move")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::MoveKey);

		PlayerEnhancedInputComponent->BindAction(DefaultInputCDO->FindInputAction(TEXT("Look")),
			ETriggerEvent::Triggered, this, &APlayerCharacter::LookKey);

		PlayerEnhancedInputComponent->BindAction(DefaultInputCDO->FindInputAction(TEXT("Jump")),
			ETriggerEvent::Started, this, &APlayerCharacter::JumpKey);

		PlayerEnhancedInputComponent->BindAction(DefaultInputCDO->FindInputAction(TEXT("Attack")),
			ETriggerEvent::Started, this, &APlayerCharacter::AttackKey);
	}
}

void APlayerCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	mTeamId = TeamID;
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return mTeamId;
}

ETeamAttitude::Type APlayerCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	// OtherTeamAgent변수가 nullptr이면 인자로 들어온 OtherActor가
	// IGenericTeamAgentInterface를 상속받지 않은 클래스라는 의미이다.
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral;

	FGenericTeamId OtherTeamId = OtherTeamAgent->GetGenericTeamId();

	if (OtherTeamId == FGenericTeamId(TeamNeutral))
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherTeamId ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

void APlayerCharacter::MoveKey(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();

	// Pitch는 빼고 Yaw만 사용(위를 볼 때 앞으로 가면 땅에 박히지 않도록)
	FRotator YawRotation(0.0, GetControlRotation().Yaw, 0.0);

	FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Axis.X);
	AddMovementInput(Right, Axis.Y);
}

// 1. 회전키 Action을 하나 더 만든다.
// 2. 마우스를 왼쪽, 오른쪽으로 움직이거나 위, 아래로 움직일 때 반응한다.
// 3. 마우스를 왼쪽, 오른쪽으로 움직일 때 SpringArm을 회전시킨다.
void APlayerCharacter::LookKey(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>() * mMouseSensitivity;

	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void APlayerCharacter::JumpKey(const FInputActionValue& Value)
{
	if (CanJump())
		Jump();
}

void APlayerCharacter::AttackKey(const FInputActionValue& Value)
{
	if (!IsValid(mAnimInst))
	{
		UE_LOG(LogTestDebug, Warning, TEXT("Invalid PlayerAnimInstance"));
		return;
	}

	mAnimInst->PlayAttack();
}

void APlayerCharacter::Attack()
{

}

void APlayerCharacter::InfoLoadComplete()
{
	UE_LOG(LogTestDebug, Warning, TEXT("InfoName : %s"), *mInfoName.ToString());

	UAssetSubsystem* AssetSubSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSubSystem)
	{
		UE_LOG(LogTestDebug, Warning, TEXT("AssetSubSystem : %s"), *mInfoName.ToString());

		const FPlayerInfo* Info = AssetSubSystem->FindPlayerInfo(mInfoName);

		// Todo : 가져오지 못하는 버그
		//if (Info)
		{
			UE_LOG(LogTestDebug, Warning, TEXT("Info : %s"), *mInfoName.ToString());

			AMainPlayerState* State = GetPlayerState<AMainPlayerState>();

			if (IsValid(State))
			{
				//UE_LOG(LogTestDebug, Warning, TEXT("Info HP : %.1f / %.1f"), Info->HP, Info->HPMax);

				State->SetAttack(50.f);
				//State->SetDefense(Info->Defense);
				State->SetHP(3000.f);
				State->SetHPMax(3000.f);

				UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

				if (Subsystem)
				{
					UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

					if (MainWidget)
					{
						State->AddHPChangeCallback<UMainWidget>(
							MainWidget,	&UMainWidget::SetNexusHP);
						State->AddHP(0.f);
					}
				}
			}
		}
	}
}
