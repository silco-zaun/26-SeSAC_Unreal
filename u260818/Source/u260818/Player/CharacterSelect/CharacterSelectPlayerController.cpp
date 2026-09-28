// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPlayerController.h"
#include "SelectPawn.h"
#include "../../UI/Select/SelectWidget.h"


ACharacterSelectPlayerController::ACharacterSelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableClickEvents = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Select/WB_Select.WB_Select_C'"));

	if (WidgetClass.Succeeded())
		mWidgetClass = WidgetClass.Class;
}

void ACharacterSelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;

	SetInputMode(InputMode);

	if (IsValid(mWidgetClass))
	{
		mWidget = CreateWidget<USelectWidget>(GetWorld(), mWidgetClass);

		if (IsValid(mWidget))
			mWidget->AddToViewport();
	}

	TArray<AActor*> FindResult;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),
		ACameraActor::StaticClass(), TEXT("MainCamera"),
		FindResult);

	if (FindResult.Num() == 1)
		mMainCamera = Cast<ACameraActor>(FindResult[0]);

	SetViewTarget(mMainCamera);

	mCurrentCamera = mMainCamera;
}

void ACharacterSelectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;

	// 마우스가 픽한 물체가 있는지 판단한다.
	bool Pick = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel6,
		false , Hit);

	if (Pick)
	{
		ASelectPawn* SelectPawn = Cast<ASelectPawn>(Hit.GetActor());

		if (SelectPawn)
		{
			// 기존에 선택된 Pawn이 있을 경우 OutLine을 끈다.
			if (mSelectPawn)
				mSelectPawn->EnableOutLine(false);

			mSelectPawn = SelectPawn;
			mSelectPawn->EnableOutLine(true);
		}
		else
		{
			if (mSelectPawn)
				mSelectPawn->EnableOutLine(false);

			mSelectPawn = nullptr;
		}
	}
	else
	{
		if (mSelectPawn)
			mSelectPawn->EnableOutLine(false);

		mSelectPawn = nullptr;
	}
}

bool ACharacterSelectPlayerController::InputKey(
	const FInputKeyEventArgs& Params)
{
	if (Params.Key == EKeys::LeftMouseButton)
	{
		if (Params.Event == IE_Pressed)
		{
			if (!mSelectPawn)
			{
				UE_LOG(Sac8Debug, Warning, TEXT("Pawn is not selected."));

				mWidget->EnableStartButton(false);

				if (mCurrentCamera != mMainCamera)
				{
					SetViewTargetWithBlend(mMainCamera, 1.f,
						EViewTargetBlendFunction::VTBlend_Cubic, 0.f, true);
					mCurrentCamera = mMainCamera;
				}
			}
			else
			{
				UE_LOG(Sac8Debug, Warning, TEXT("%s is selected."), *mSelectPawn->GetName());

				mWidget->EnableStartButton(true);
				mWidget->EnableSelectInfo(true);
				mWidget->SetCharacterImage(mSelectPawn->GetPlayerJob());
				mWidget->SetSelectJob(mSelectPawn->GetPlayerJob());

				// SelectPawn을 보여줄 카메라를 얻어온다.
				ACameraActor* ViewCamera = mSelectPawn->GetViewCamera();

				if (mCurrentCamera != ViewCamera)
				{
					SetViewTargetWithBlend(ViewCamera, 1.f,
						EViewTargetBlendFunction::VTBlend_Cubic, 0.f, true);
					mCurrentCamera = ViewCamera;
				}
			}
		}
		else if (Params.Event == IE_Released)
		{

		}
	}

	return Super::InputKey(Params);
}

void ACharacterSelectPlayerController::ClickActor(AActor* TouchActor,
	FKey key)
{

}
