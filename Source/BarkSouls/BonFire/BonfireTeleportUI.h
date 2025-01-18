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
    // Stage ��ư
    UPROPERTY(meta = (BindWidget))
    class UButton* Stage1Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage2Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage3Button;

    // ȭ��� ��ư ��� ǥ��
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* BonfireList;

    // ������ ȭ��� ������ (������ ������)
    TMap<FName, TArray<FBonfireData>> LevelBonfireMap;

    TMap<UButton*, FName> ButtonToBonfireIDMap;

public:
    // UI �ʱ�ȭ �Լ�
    void InitializeUI(const TMap<FName, FBonfireData>& InLevelBonfireMap);

    // Stage ��ư Ŭ�� �Լ�
    UFUNCTION()
    void OnStage1ButtonClicked();

    UFUNCTION()
    void OnStage2ButtonClicked();

    UFUNCTION()
    void OnStage3ButtonClicked();

    // ȭ��� ��ư Ŭ�� �Լ�
    UFUNCTION()
    void OnBonfireButtonClicked();


protected:
    // Ư�� Stage�� ���� ȭ��� ��� ����
    void PopulateBonfireList(const TArray<FBonfireData>& Bonfires);

    // Ư�� Bonfire�� �̵�
    void TeleportToBonfire(FName BonfireID);
};