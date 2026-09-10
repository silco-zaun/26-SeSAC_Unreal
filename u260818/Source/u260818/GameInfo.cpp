#include "GameInfo.h"

// 로그 정의
DEFINE_LOG_CATEGORY(Sac8Debug);

FRotator GetTargetRotation(const FVector& Target, const FVector& Self)
{
	return UKismetMathLibrary::FindLookAtRotation(Self, Target);
}

FRotator GetTargetRotationYaw(FVector Target, FVector Self)
{
	Target.Z = 0.f;
	Self.Z = 0.f;

	return FRotator();
}

bool GetRandomNavigationPoint(FVector& Result, UWorld* World,
	const FVector& Center, float Radius)
{
	// 현재 내비게이션 시스템을 얻어온다.
	UNavigationSystemV1* NavSystem =
		FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

	if (!NavSystem)
		return false;

	FNavLocation ResultNavLoc;
	if (NavSystem->GetRandomPointInNavigableRadius(Center, Radius,
		ResultNavLoc))
	{
		Result = ResultNavLoc.Location;

		return true;
	}

	return false;
}
