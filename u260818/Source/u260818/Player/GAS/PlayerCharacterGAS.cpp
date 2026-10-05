// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterGAS.h"
#include "../PlayerAnimInstance.h"
#include "../MainPlayerState.h"
#include "../../Subsystem/AssetSubsystem.h"
#include "../../Subsystem/UISubsystem.h"
#include "../../UI/Main/MainWidget.h"
#include "../InventoryComponent.h"
#include "../../UI/Main/WorldInfoWidget.h"
#include "../../ShareComponent/BillboardWidgetComponent.h"
#include "PlayerASC.h"
#include "PlayerAttributeSet.h"

// Sets default values
APlayerCharacterGAS::APlayerCharacterGAS()
{
	PrimaryActorTick.bCanEverTick = true;

	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	mHPBarWC = CreateDefaultSubobject<UBillboardWidgetComponent>(TEXT("HPBar"));
	mASC = CreateDefaultSubobject<UPlayerASC>(TEXT("ASC"));

	mArm->SetupAttachment(GetMesh());

	mCamera->SetupAttachment(mArm);

	mArm->TargetArmLength = 500.f;

	mHPBarWC->SetupAttachment(GetMesh(), TEXT("HealthBar"));

	// 충돌 설정
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	SetGenericTeamId(FGenericTeamId(TeamPlayer));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		HPWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/WB_WorldInfo.WB_WorldInfo'"));

	if (HPWidgetClass.Succeeded())
	{
		mHPBarWC->SetWidgetClass(HPWidgetClass.Class);
	}

	//mHPBarWC->SetWIdgetSpace(EWidgetSpace::Screen);
	mHPBarWC->SetWidgetSpace(EWidgetSpace::World);
	mHPBarWC->SetDrawSize(FVector2D(200.0, 80.0));
	mHPBarWC->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 양면을 모두 보이게 한다.
	mHPBarWC->SetTwoSided(true);

	GetMesh()->SetRenderCustomDepth(true);

	// Player Attribute Set을 생성한다.
	mAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	// 생성한 PlayerAttributeSet을 ASC에 등록한다.
	mASC->AddAttributeSetSubobject<UPlayerAttributeSet>(mAttributeSet);
}

FVector APlayerCharacterGAS::GetImpactLocation() const
{
	return GetMesh()->GetSocketLocation(TEXT("Impact"));
}

// Called when the game starts or when spawned
void APlayerCharacterGAS::BeginPlay()
{
	Super::BeginPlay();

	// WidgetComponent가 생성한 위젯을 얻어온다.
	mWorldInfo = Cast<UWorldInfoWidget>(mHPBarWC->GetWidget());

	UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();


	if (AssetSystem)
	{
		if (AssetSystem->GetLoadPlayerInfo())
		{
			InfoLoadComplete();
		}
		else
		{
			AssetSystem->AddPlayerDataAssetLoadingDelegate(this, &APlayerCharacterGAS::InfoLoadComplete);
		}
	}

	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// InputMappingConstext를 지정한다.
	// PlayerController를 얻어온다.
	// Pawn종류는 자신에게 빙의된 컨트롤러를 반환하는 기능을 제공한다.
	// 언리얼엔진에서는 Cast 함수를 이용해서 UObject에 대한 형변환을
	// 진행한다.
	TObjectPtr<APlayerController> PlayerController =
		Cast<APlayerController>(GetController());
	
	// UObject타입 객체가 유효한 객체인지를 체크한다.
	if (IsValid(PlayerController))
	{
		// PlayerController가 가지고 있는 InputSystem을 얻어온다.
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// InputMappingContext를 가지고 있는 CDO를 얻어온다.
		const UTestInput* InputCDO = GetDefault<UTestInput>();

		// InputMappingContext를 InputSystem에 등록한다.
		InputSystem->AddMappingContext(InputCDO->mContext, 0);
	}
}

// Called every frame
void APlayerCharacterGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacterGAS::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
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

		// 1번인자 : 바인딩할 InputAction을 지정한다.
		// 2번인자 : 이 Action에 지정된 Key가 어떻게 반응할지 지정한다.
		// 3번인자 : 이 Action이 동작할 때 호출할 함수를 가지고 있는 UObject
		// 객체를 지정한다.
		// 4번인자 : 이 Action이 동작할 때 호출할 함수의 주소를 지정한다.
		Input->BindAction(InputCDO->FindAction(TEXT("Move")),
			ETriggerEvent::Triggered, this, &APlayerCharacterGAS::MoveKey);

		Input->BindAction(InputCDO->FindAction(TEXT("RotChar")),
			ETriggerEvent::Triggered, this,
			&APlayerCharacterGAS::RotationCharacterKey);

		Input->BindAction(InputCDO->FindAction(TEXT("RotCamera")),
			ETriggerEvent::Triggered, this,
			&APlayerCharacterGAS::RotationCameraKey);

		Input->BindAction(InputCDO->FindAction(TEXT("CameraZoom")),
			ETriggerEvent::Triggered, this,
			&APlayerCharacterGAS::CameraZoomKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Jump")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::JumpKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Attack")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::AttackKey);

		Input->BindAction(InputCDO->FindAction(TEXT("HitTest")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::HitKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill1")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::Skill1Key);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill1")),
			ETriggerEvent::Completed, this,
			&APlayerCharacterGAS::Skill1ReleaseKey);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill2")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::Skill2Key);

		Input->BindAction(InputCDO->FindAction(TEXT("Skill3")),
			ETriggerEvent::Started, this,
			&APlayerCharacterGAS::Skill3Key);
	}
}

float APlayerCharacterGAS::TakeDamage(float DamageAmount,
	FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	if (DamageAmount > 0.f)
	{
		AMainPlayerState* State = Cast<AMainPlayerState>(GetPlayerState());

		DamageAmount = DamageAmount - State->GetDefense();

		DamageAmount = FMath::Max(DamageAmount, 1.0f);

		if (!State->AddHP(-DamageAmount))
		{
			//Destroy();
		}
	}

	return DamageAmount;
}

void APlayerCharacterGAS::MoveKey(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	
	FVector MoveDir = Forward * Axis.X + Right * Axis.Y;

	// 이동 방향 백터를 정규화한다.
	MoveDir.Normalize();

	AddMovementInput(MoveDir, 1.f);
}

void APlayerCharacterGAS::RotationCharacterKey(
	const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();

	AddControllerYawInput(Axis);
}

void APlayerCharacterGAS::RotationCameraKey(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();

	mArm->AddRelativeRotation(FRotator(Axis.Y, Axis.X, 0.0));

	mAnimInst->AddViewYaw(Axis.X);
	mAnimInst->AddViewPitch(Axis.Y);
}

void APlayerCharacterGAS::CameraZoomKey(const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();

	mArm->TargetArmLength -= Axis * 30.f;

	if (mArm->TargetArmLength < 150.f)
		mArm->TargetArmLength = 150.f;
	else if (mArm->TargetArmLength > 500.f)
		mArm->TargetArmLength = 500.f;
}

void APlayerCharacterGAS::JumpKey(const FInputActionValue& Value)
{
	if (CanJump())
		Jump();
}

void APlayerCharacterGAS::AttackKey(const FInputActionValue& Value)
{
	mAnimInst->PlayAttack();
}

void APlayerCharacterGAS::HitKey(const FInputActionValue& Value)
{
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

void APlayerCharacterGAS::Skill1Key(const FInputActionValue& Value)
{
	UE_LOG(Sac8Debug, Warning, TEXT("Skill1"));
	Skill1();
}

void APlayerCharacterGAS::Skill1ReleaseKey(const FInputActionValue& Value)
{
	UE_LOG(Sac8Debug, Warning, TEXT("Skill1 Release"));
	Skill1Release();
}

void APlayerCharacterGAS::Skill2Key(const FInputActionValue& Value)
{
	Skill2();
}

void APlayerCharacterGAS::Skill3Key(const FInputActionValue& Value)
{
	Skill3();
}

void APlayerCharacterGAS::Attack()
{
}

void APlayerCharacterGAS::Death()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCharacterMovement()->StopMovementImmediately();

	GetMesh()->bPauseAnims = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	GetMesh()->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	GetMesh()->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	GetMesh()->SetAllBodiesSimulatePhysics(false);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("pelvis"), true, true);

	// 바디의 Sleep 상태를 깨워준다.
	GetMesh()->WakeAllRigidBodies();

	// 애니메이션 포즈와 물리 결과를 섞어서 반영하도록 한다.
	GetMesh()->bBlendPhysics = true;
}

void APlayerCharacterGAS::Skill1()
{
}

void APlayerCharacterGAS::Skill1Release()
{
}

void APlayerCharacterGAS::Skill2()
{
}

void APlayerCharacterGAS::Skill3()
{
}

void APlayerCharacterGAS::InfoLoadComplete()
{
	UAssetSubsystem* AssetSystem = GetGameInstance()->GetSubsystem<UAssetSubsystem>();

	if (AssetSystem)
	{
		const FPlayerInfo* Info = AssetSystem->FindPlayerInfo(mInfoName);

		if (Info)
		{
			AMainPlayerState* State = GetPlayerState<AMainPlayerState>();

			if (IsValid(State))
			{
				//State->SetPlayerName(Info->PlayerName);
				State->SetPlayerJob(Info->Job);
				State->SetAttack(Info->Attack);
				State->SetDefense(Info->Defense);
				State->SetHP(Info->HP);
				State->SetHPMax(Info->HPMax);
				State->SetMP(Info->MP);
				State->SetMPMax(Info->MPMax);
				State->SetLevel(Info->Level);
				State->SetExp(Info->Exp);
				State->SetGold(Info->Gold);
				State->SetMoveSpeed(Info->MoveSpeed);
				State->SetAttackSpeed(Info->AttackSpeed);
				State->SetAttackDistance(Info->AttackDistance);

				State->AddHPChangeCallback<APlayerCharacterGAS>(this,
					&APlayerCharacterGAS::ChangeHP);
			}

			mWorldInfo->SetInfoName(State->GetPlayerName());

			UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

			if (Subsystem)
			{
				UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

				if (MainWidget)
				{
					MainWidget->SetPlayerName(State->GetPlayerName());
					State->AddHPChangeCallback<UMainWidget>(MainWidget,
						&UMainWidget::SetPlayerHP);
				}
			}

			mAttributeSet->SetAttack(Info->Attack);
			mAttributeSet->SetDefense(Info->Defense);
			mAttributeSet->SetHP(Info->HP);
			mAttributeSet->SetHPMax(Info->HPMax);
			mAttributeSet->SetMP(Info->MP);
			mAttributeSet->SetMPMax(Info->MPMax);
			mAttributeSet->SetLevel(Info->Level);
			mAttributeSet->SetExp(Info->Exp);
			mAttributeSet->SetGold(Info->Gold);
			mAttributeSet->SetMoveSpeed(Info->MoveSpeed);
			mAttributeSet->SetAttackSpeed(Info->AttackSpeed);
			mAttributeSet->SetAttackDistance(Info->AttackDistance);
			mAttributeSet->SetJob((float)Info->Job);
		}
	}
}

void APlayerCharacterGAS::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	mTeamId = TeamID;
}

FGenericTeamId APlayerCharacterGAS::GetGenericTeamId() const
{
	return mTeamId;
}

ETeamAttitude::Type APlayerCharacterGAS::GetTeamAttitudeTowards(
	const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	// OtherTeamAgent변수가 nullptr이면 인자로 들어온 OtherActor가
	// IGenericTeamAgentInterface를 상속받지 않은 클래스라는 의미이다.
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral;

	else if (OtherTeamAgent->GetGenericTeamId() ==
		FGenericTeamId(TeamNeutral))
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

bool APlayerCharacterGAS::AddInventoryItem(const FItemTableInfo& ItemInfo)
{
	return mInventory->AddItem(ItemInfo);
}

void APlayerCharacterGAS::ChangeHP(float HP, float HPMax)
{
	mWorldInfo->SetHP(HP, HPMax);
}

void APlayerCharacterGAS::EnableOutLine(bool Enable)
{
	if (Enable)
	{
		int32 Value = GetMesh()->CustomDepthStencilValue | 1;
		GetMesh()->SetCustomDepthStencilValue(Value);
	}
	else
	{
		if (GetMesh()->CustomDepthStencilValue & 1)
			GetMesh()->SetCustomDepthStencilValue(GetMesh()->CustomDepthStencilValue ^ 1);
	}
}

UAbilitySystemComponent* APlayerCharacterGAS::GetAbilitySystemComponent() const
{
	return mASC;
}
