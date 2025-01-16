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

public:
    // ScrollBox�� �߰��� ��ư��
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* BonfireList;

    // ��ư�� ID�� ����
    TMap<UButton*, FName> ButtonIDMap;

    // ȭ��� UI �ʱ�ȭ �Լ�
    UFUNCTION(BlueprintCallable)
    void InitializeTeleportUI(const TMap<FName, FBonfireData>& ActiveBonfires);

    // ��ư Ŭ�� �̺�Ʈ �Լ�
    UFUNCTION()
    void OnBonfireClicked();

protected:
    virtual void NativeConstruct() override; // �ʱ�ȭ
};