// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "../UI/Main/MainWidget.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	// 마우스 커서를 보이게 한다.
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		MainWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/WB_Main.WB_Main_C'"));

	if (MainWidgetClass.Succeeded())
		mMainWidgetClass = MainWidgetClass.Class;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 입력 모드를 세팅한다.
	// FInputModeGameOnly
	// FInputModeGameAndUI
	// FInputModeUIOnly
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);

	// 위젯을 생성한다.
	mMainWidget = CreateWidget<UMainWidget>(this, mMainWidgetClass);

	if (IsValid(mMainWidget))
	{
		// AddToViewport를 통해 위젯을 뷰포트에 붙여준다.
		// 이 함수는 인자로 ZOrder가 들어가는데 여러개의 위젯을 붙이고 ZOrder로
		// 출력되는 순서를 컨트롤 할 수 있다.
		mMainWidget->AddToViewport();
	}
}

void AMainPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMainPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMainPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
