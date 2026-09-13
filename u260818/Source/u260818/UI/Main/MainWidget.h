// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class U260818_API UMainWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UMainWidget(const FObjectInitializer& ObjectInitializer);

protected:
	// 위젯 블루프린트에서 배치한 위젯이 변수여부 체크가 되어있을 경우
	// UPROPERTY의 meta에 BindWidget을 이용해서 배치한 위젯의 객체를
	// 얻어올 수 있다. 변수 이름은 반드시 위젯 블루프린트에서 작성한 이름과
	// 동일해야 한다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UInventoryWidget> mInventory;

protected:
	virtual void NativeOnInitialized();
};
