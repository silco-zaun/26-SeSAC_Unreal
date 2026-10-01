// Fill out your copyright notice in the Description page of Project Settings.


#include "WukongProjectile.h"

AWukongProjectile::AWukongProjectile()
{
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	mParticle->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(
		TEXT("/Script/Engine.ParticleSystem'/Game/ParagonWraith/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_Trail.P_Wraith_Primary_Trail'"));

	if (Particle.Succeeded())
		mParticle->SetTemplate(Particle.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterial(
		TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Fab/Megascans/Decals/High_Velocity_Blood_Spatter_sgeoahup/Medium/sgeoahup_tier_2/Materials/MI_sgeoahup.MI_sgeoahup'"));

	if (DecalMaterial.Succeeded())
		mDecalMaterial = DecalMaterial.Object;

	mMovement->ProjectileGravityScale = 1.f;

	mMovement->InitialSpeed = 2000.f;

	mBody->SetCollisionProfileName(TEXT("PlayerAttack"));
}

void AWukongProjectile::StopCallback(const FHitResult& ImpactResult)
{
	Destroy();
}