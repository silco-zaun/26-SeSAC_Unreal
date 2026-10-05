// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"

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

	//mMesh->SetCanEverAffectNavigation(false);

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

