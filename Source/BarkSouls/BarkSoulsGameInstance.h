// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BarkSouls/BonFire/BonfireTypes.h"
#include "BarkSoulsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBarkSoulsGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:

public:
	virtual void Init() override;

	// ���� �� ��� ȭ��� ������ ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, FBonfireData> BonfireMap;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FName SelectedBonfire;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Fade")
	bool bShouldFadeIn = false;



	void RegisterBonfire(FBonfireData NewBonfire); // ȭ��� ���� �Լ�

	void SetSelectedBonfire(FName BonfireName); // � ȭ����� ����Ǿ����� Ȯ���ϴ� �Լ�

	FTransform GetBonfireTransform(FName BonfireID); // ȭ��� ��ġ ��ȯ�Լ�
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsMainMenuActive = true; // ���� �޴� UI�� �ٽ� �������� ���θ� �����ϴ� ����

};
