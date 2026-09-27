// Fill out your copyright notice in the Description page of Project Settings.


#include "BillboardWidgetComponent.h"

UBillboardWidgetComponent::UBillboardWidgetComponent(const FObjectInitializer& PCIP) :
	Super(PCIP)
{
	SetPivot(FVector2D(0.5, 1.0));
	SetRelativeScale3D(FVector(1.0, 0.3, 0.3));
}

void UBillboardWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerCameraManager* CamMgr =
		UGameplayStatics::GetPlayerCameraManager(this, 0);

	if (CamMgr)
	{
		// 카메라를 바라보게 회전시킨다.
		FVector CameraPos = CamMgr->GetCameraLocation();
		FVector SelfPos = GetComponentLocation();

		FRotator LookAt = GetTargetRotation(CameraPos, SelfPos);
		SetWorldRotation(LookAt);
	}
}
