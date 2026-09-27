// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "../Subsystem/UISubsystem.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UBaseWidget::PlayWidgetAnimation(const FString& Name, float StartTime, 
	float PlaySpeed, bool Forward, bool RestoreState, int32 LoopCount)
{
	TObjectPtr<UWidgetAnimation> Anim = mAnimMap.FindRef(Name);

	if (IsValid(Anim))
	{
		EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward;

		if (!Forward)
			PlayMode = EUMGSequencePlayMode::Reverse;

		PlayAnimation(Anim, StartTime, LoopCount, PlayMode,
			PlaySpeed, RestoreState);
	}
}

void UBaseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		Subsystem->AddWidget(mWidgetName, this);
	}

	// 위젯 애니메이션이 있을 경우 Map에 추가한다.
	UWidgetBlueprintGeneratedClass* GeneratedClass = GetWidgetTreeOwningClass();

	for (auto& Anim : GeneratedClass->Animations)
	{
		FString Name = Anim->GetName();

		// 애니메이션 이름 뒤에 _INST가 붙기 때문에 제거한다.
		Name.ReplaceInline(TEXT("_INST"), TEXT(""));

		mAnimMap.Add(Name, Anim);
	}
}

void UBaseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

	if (Subsystem)
	{
		Subsystem->RemoveWidget(mWidgetName);
	}
}

void UBaseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


