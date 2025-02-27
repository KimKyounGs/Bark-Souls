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

	// 게임 내 모든 화톳불 데이터 저장
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FName, FBonfireData> BonfireMap;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FName SelectedBonfire;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Fade")
	bool bShouldFadeIn = false;



	void RegisterBonfire(FBonfireData NewBonfire); // 화톳불 저장 함수

	void SetSelectedBonfire(FName BonfireName); // 어떤 화톳불이 저장되었는지 확인하는 함수

	FTransform GetBonfireTransform(FName BonfireID); // 화톳불 위치 반환함수
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsMainMenuActive = true; // 메인 메뉴 UI를 다시 생성할지 여부를 저장하는 변수

};
