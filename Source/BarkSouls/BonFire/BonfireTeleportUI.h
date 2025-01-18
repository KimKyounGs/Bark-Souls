// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireTypes.h"
#include "Components/Button.h"
#include "BonfireTeleportUI.generated.h"

UCLASS()
class BARKSOULS_API UBonfireTeleportUI : public UUserWidget
{
    GENERATED_BODY()

protected:
    // Stage 버튼
    UPROPERTY(meta = (BindWidget))
    class UButton* Stage1Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage2Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage3Button;

    // 화톳불 버튼 목록 표시
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* BonfireList;

    // 레벨별 화톳불 데이터 (고정된 데이터)
    TMap<FName, TArray<FBonfireData>> LevelBonfireMap;

    TMap<UButton*, FName> ButtonToBonfireIDMap;

public:
    // UI 초기화 함수
    void InitializeUI(const TMap<FName, FBonfireData>& InLevelBonfireMap);

    // Stage 버튼 클릭 함수
    UFUNCTION()
    void OnStage1ButtonClicked();

    UFUNCTION()
    void OnStage2ButtonClicked();

    UFUNCTION()
    void OnStage3ButtonClicked();

    // 화톳불 버튼 클릭 함수
    UFUNCTION()
    void OnBonfireButtonClicked();


protected:
    // 특정 Stage에 따라 화톳불 목록 갱신
    void PopulateBonfireList(const TArray<FBonfireData>& Bonfires);

    // 특정 Bonfire로 이동
    void TeleportToBonfire(FName BonfireID);
};