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

};