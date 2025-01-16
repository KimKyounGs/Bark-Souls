// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonFire.h"
#include "BonfireUI.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBonfireUI : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestButton; 

	UPROPERTY(meta = (BindWidget))
	class UButton* TeleportButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LeaveButton;

	ABonfire* bonfire;
protected:
	virtual void NativeConstruct() override; // ���� ���� �� �ʱ�ȭ �ϴ� �Լ�.
public:
	UFUNCTION()
	void OnRestButtonClicked();
	
	UFUNCTION()
	void OnTeleportButtonClicked();

	UFUNCTION()
	void OnLeaveButtonClikced();
};
