// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireTypes.h"
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
    class UScrollBox* BonfireScrollBox; 

    UPROPERTY(meta = (BindWidget))
    class UWrapBox* BonfireWrapBox;  

    // 돌아가기 버튼
    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    // 현재 선택된 Stage
    FName CurrentStage;

    TMap<UButton*, FName> ButtonStageMap;


    TMap<UButton*, FName> ButtonBonfireMap;

    class AUIManager* UIManager;

public:
    // Stage 버튼 클릭 이벤트
    UFUNCTION()
    void OnStageButtonClicked();

    UFUNCTION()
    void OnBackButtonClicked();

    // 특정 Stage의 화톳불 목록을 UI에 표시
    void PopulateBonfireList(FName StageName);

    UFUNCTION()
    void OnAnyBonfireButtonClicked();

    UFUNCTION()
    // 특정 Bonfire로 이동
    void TeleportToBonfire(FName BonfireID);

    // 화톳불 데이터 저장.
    // void ReserveBonfire();
};