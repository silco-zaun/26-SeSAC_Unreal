// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "../Player/PlayerCharacter.h"
#include "../Player/MainPlayerState.h"
#include "../Subsystem/UISubsystem.h"
#include "../UI/Main/MainWidget.h"

// Sets default values
ANexus::ANexus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));

	SetRootComponent(mCapsule);
	mMesh->SetupAttachment(mCapsule);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);

	mCapsule->SetCapsuleHalfHeight(150.f);
	mCapsule->SetCapsuleRadius(150.f);
	mMesh->SetRelativeScale3D(FVector(3.0, 3.0, 3.0));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		MtrlAsset(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (MtrlAsset.Succeeded())
		mMesh->SetMaterial(0, MtrlAsset.Object);

	// Nexus가 NavMesh에 구멍을 뚫으면 Nexus 중심점을 NavMesh에 투영할 수 없어
	// MoveToActor의 경로 탐색이 실패한다. 네비게이션에 영향을 주지 않게 한다.
	// (Capsule도 BlockAllDynamic 프로필이므로 같이 꺼야 한다)
	mCapsule->SetCanEverAffectNavigation(false);
	mMesh->SetCanEverAffectNavigation(false);

	//mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//mCapsule->SetCollisionProfileName(TEXT("Nexus"));
	//mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetGenericTeamId(FGenericTeamId(TeamPlayer));
}

// Called when the game starts or when spawned
void ANexus::BeginPlay()
{
	Super::BeginPlay();

	// Sight 감지 대상으로 등록한다. (Pawn이 아닌 Actor는 자동 등록되지 않는다)
	mStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	mStimuliSource->RegisterWithPerceptionSystem();
	
	UMaterialInstanceDynamic* Material = mMesh->CreateDynamicMaterialInstance(0);
	if (Material)
		Material->SetVectorParameterValue(TEXT("Color"), FLinearColor::Yellow);
}

// Called every frame
void ANexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANexus::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	mTeamId = TeamID;
}

FGenericTeamId ANexus::GetGenericTeamId() const
{
	return mTeamId;
}

ETeamAttitude::Type ANexus::GetTeamAttitudeTowards(const AActor& Other) const
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

float ANexus::TakeDamage(float DamageAmount,
	struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DamageCauser);

	if (IsValid(PlayerCharacter))
		return DamageAmount;

	UE_LOG(LogTestDebug, Warning, TEXT("Nexus Damage : %.2f"), DamageAmount);

	if (DamageAmount > 0.f)
	{
		AMainPlayerState* State = 
			Cast<AMainPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

		if (!State->AddHP(-DamageAmount))
		{
			UUISubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUISubsystem>();

			if (Subsystem)
			{
				UMainWidget* MainWidget = Subsystem->FindWidget<UMainWidget>(TEXT("Main"));

				if (MainWidget)
				{
					MainWidget->SetResultText(TEXT("패배"));
				}
			}

			Destroy();
		}
	}

	return DamageAmount;
}

