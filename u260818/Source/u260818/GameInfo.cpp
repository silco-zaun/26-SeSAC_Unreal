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

FString ConvertItemOptionName(EItemOptionType Type)
{
	switch (Type)
	{
	case EItemOptionType::Attack:
		return TEXT("Attack");
	case EItemOptionType::Defense:
		return TEXT("Defense");
	case EItemOptionType::HPMax:
		return TEXT("HPMax");
	case EItemOptionType::MPMax:
		return TEXT("MPMax");
	case EItemOptionType::HPRecovery:
		return TEXT("HPRecovery");
	case EItemOptionType::MPRecovery:
		return TEXT("MPRecovery");
	case EItemOptionType::MoveSpeed:
		return TEXT("MoveSpeed");
	case EItemOptionType::AttackSpeed:
		return TEXT("AttackSpeed");
	case EItemOptionType::AttackDistance:
		return TEXT("AttackDistance");
	case EItemOptionType::CriticalRatio:
		return TEXT("CriticalRatio");
	case EItemOptionType::CriticalDamage:
		return TEXT("CriticalDamage");
	}

	return TEXT("");
}
