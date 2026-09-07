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
