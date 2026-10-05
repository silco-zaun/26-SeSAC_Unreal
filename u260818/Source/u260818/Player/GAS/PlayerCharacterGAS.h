// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Input/Input.h"
#include "../../Render/OutLineInterface.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterGAS.generated.h"

UCLASS()
class U260818_API APlayerCharacterGAS : public ACharacter,
	public IGenericTeamAgentInterface, public IOutLineInterface,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterGAS();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> mArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> mCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInventoryComponent> mInventory;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBillboardWidgetComponent> mHPBarWC;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPlayerASC> mASC;

	TObjectPtr<class UWorldInfoWidget> mWorldInfo;

	// SkeletalMeshComponent가 생성한 AnimInstance객체의 주소를 저장하기
	// 위한 변수
	UPROPERTY()
	TObjectPtr<class UPlayerAnimInstance> mAnimInst;

	FName mInfoName;

	FGenericTeamId mTeamId;

	TObjectPtr<class UPlayerAttributeSet> mAttributeSet;

public:
	FVector GetImpactLocation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	void Skill2Key(const FInputActionValue& Value);
	void Skill3Key(const FInputActionValue& Value);

public:
	virtual void Attack();
	virtual void Death();
	virtual void Skill1();
	virtual void Skill1Release();
	virtual void Skill2();
	virtual void Skill3();

public:
	UFUNCTION()
	void InfoLoadComplete();

public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId() const;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

public:
	bool AddInventoryItem(const FItemTableInfo& ItemInfo);

protected:
	void ChangeHP(float HP, float HPMax);

	// interface
public:
	virtual void EnableOutLine(bool Enable);

public:
	// IAbilitySystemInterface에서 이 함수는 순수가상함수로 되어 있기 때문에 반드시 재정의해야 한다.
	// GAS 내부 프레임워크에서 이 함수를 호출하여 AbilitySystemComponent를 얻어온다.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
};
