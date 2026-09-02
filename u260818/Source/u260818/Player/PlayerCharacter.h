// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Input/Input.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class U260818_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> mArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> mCamera;

	UPROPERTY()
	TObjectPtr<class UPlayerAnimInstance> mAnimInst;

	FName mInfoName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Apply damage to this actor.
	 * @see https://www.unrealengine.com/blog/damage-in-ue4
	 * @param DamageAmount      How much damage to apply
	 * @param DamageEvent      Data package that fully describes the damage received.
	 * @param EventInstigator   The Controller responsible for the damage.
	 * @param DamageCauser      The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return               The amount of damage actually applied.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:
	void MoveKey(const FInputActionValue& Value);
	void RotationCharacterKey(const FInputActionValue& Value);
	void RotationCameraKey(const FInputActionValue& Value);
	void CameraZoomKey(const FInputActionValue& Value);
	void JumpKey(const FInputActionValue& Value);
	void AttackKey(const FInputActionValue& Value);
	void HitKey(const FInputActionValue& Value);
	void Skill1Key(const FInputActionValue& Value);
	void Skill1ReleaseKey(const FInputActionValue& Value);

public:
	virtual void Attack();
	virtual void Death();
	virtual void Skill1();
	virtual void Skill1Release();

public:
	UFUNCTION()
	void InfoLoadComplete();

};
