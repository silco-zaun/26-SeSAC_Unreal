// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class U260818_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// TObjectPtr은 언리얼 UObject를 상속받은 객체의 주소를 가지고 있을때
	// 사용한다.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mChildMesh;

	// VisibleAnywhere : 에디터에서 보여지게 만들 때 사용한다.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> mRotMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
