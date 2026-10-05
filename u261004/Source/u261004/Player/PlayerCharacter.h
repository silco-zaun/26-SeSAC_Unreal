// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../Input/Input.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class U261004_API APlayerCharacter : public ACharacter,
	public IGenericTeamAgentInterface
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float mMouseSensitivity = 0.5f;

	UPROPERTY()
	TObjectPtr<class UPlayerAnimInstance> mAnimInst;

	FName mInfoName;

	FGenericTeamId mTeamId;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

private:
	void MoveKey(const FInputActionValue& Value);
	void LookKey(const FInputActionValue& Value);
	void JumpKey(const FInputActionValue& Value);
	void AttackKey(const FInputActionValue& Value);

public:
	virtual void Attack();

public:
	UFUNCTION()
	void InfoLoadComplete();
};
