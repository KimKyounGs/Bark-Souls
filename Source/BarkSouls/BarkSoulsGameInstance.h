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
public:
	virtual void Init() override;

	// 게임 내 모든 화톳불 데이터 저장
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, FBonfireData> BonfireMap;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FName SelectedBonfire;

	void RegisterBonfire(FBonfireData NewBonfire);

	void SetSelectedBonfire(FName BonfireName);

	FTransform GetBonfireTransform(FName BonfireID);
	
};
