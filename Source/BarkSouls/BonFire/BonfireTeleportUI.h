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
    // Stage ��ư
    UPROPERTY(meta = (BindWidget))
    class UButton* Stage1Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage2Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* Stage3Button;

    // ȭ��� ��ư ��� ǥ��
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* BonfireScrollBox; 

    UPROPERTY(meta = (BindWidget))
    class UWrapBox* BonfireWrapBox;  

    // ���ư��� ��ư
    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    // ���� ���õ� Stage
    FName CurrentStage;

    TMap<UButton*, FName> ButtonStageMap;


    TMap<UButton*, FName> ButtonBonfireMap;

    class AUIManager* UIManager;

public:
    // Stage ��ư Ŭ�� �̺�Ʈ
    UFUNCTION()
    void OnStageButtonClicked();

    UFUNCTION()
    void OnBackButtonClicked();

    // Ư�� Stage�� ȭ��� ����� UI�� ǥ��
    void PopulateBonfireList(FName StageName);

    UFUNCTION()
    void OnAnyBonfireButtonClicked();

    UFUNCTION()
    // Ư�� Bonfire�� �̵�
    void TeleportToBonfire(FName BonfireID);

    // ȭ��� ������ ����.
    // void ReserveBonfire();
};