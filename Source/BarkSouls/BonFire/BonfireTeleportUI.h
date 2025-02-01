// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BonfireTypes.h"
#include "BarkSouls/Character/DogCharacterController.h" // ���� ��Ʈ�ѷ� ����
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
    class UScrollBox* BonfireList;

    // ���ư��� ��ư
    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    // ���� ���õ� Stage
    FName CurrentStage;

    // Stage�� ȭ��� ������
    TMap<FName, TArray<FBonfireData>> BonfireMap;

    // ��ư�� ȭ��� ID ����
    TMap<UButton*, FName> ButtonToBonfireIDMap;

    class ADogCharacterController* DogController;

public:
    // Stage ��ư Ŭ�� �̺�Ʈ
    UFUNCTION()
    void OnStageButtonClicked();

    UFUNCTION()
    void OnBackButtonClicked();

    // Ư�� Stage�� ȭ��� ����� UI�� ǥ��
    void PopulateBonfireList(FName StageName);

    // Ư�� Bonfire�� �̵�
    void TeleportToBonfire(FName BonfireID);
};