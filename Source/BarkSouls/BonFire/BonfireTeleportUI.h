// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BonfireTypes.h"
#include "BarkSouls/Character/DogCharacterController.h" // 기존 컨트롤러 포함
#include "BonfireTeleportUI.generated.h"

UCLASS()
class BARKSOULS_API UBonfireTeleportUI : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

private:
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

    // 돌아가기 버튼
    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    // 현재 선택된 Stage
    FName CurrentStage;

    // Stage별 화톳불 데이터
    TMap<FName, TArray<FBonfireData>> BonfireMap;

    // 버튼과 화톳불 ID 매핑
    TMap<UButton*, FName> ButtonToBonfireIDMap;

    class ADogCharacterController* DogController;

public:
    // Stage 버튼 클릭 이벤트
    UFUNCTION()
    void OnStageButtonClicked();

    UFUNCTION()
    void OnBackButtonClicked();

    // 특정 Stage의 화톳불 목록을 UI에 표시
    void PopulateBonfireList(FName StageName);

    // 특정 Bonfire로 이동
    void TeleportToBonfire(FName BonfireID);
};