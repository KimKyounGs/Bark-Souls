// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

/**
 * UI Enum ���� : UI �̸��� Enum���� ����
 */
UENUM(BlueprintType)
enum class EUIType : uint8
{
    BonfireUI,
    BonfireTeleportUI,
    InventoryUI,
    PauseMenuUI
};

/**
 * UIManager : UI�� �߾ӿ��� �����ϴ� Ŭ����
 */
UCLASS()
class BARKSOULS_API UUIManager : public UObject
{
	GENERATED_BODY()
private:
    // ���� Ȱ��ȭ�� UI
    UPROPERTY(EditAnywhere)
    UUserWidget* CurrentUI;

    // ��� UI�� �����ϴ� TMap
    UPROPERTY()
    TMap<EUIType, UUserWidget*> UIMap;

    // �÷��̾� ��Ʈ�ѷ�
    UPROPERTY()
    class APlayerController* PlayerController;


public:
    // �����Ϳ��� ���� ������ UI Ŭ���� ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TMap<EUIType, TSubclassOf<UUserWidget>> UIClassMap;

    // Initialize �Լ�
    void Initialize(APlayerController* InPlayerController);

    // UI ���� ��ȯ
    void ShowUI(EUIType UIType);

    // ���� Ȱ��ȭ�� UI �����
    void HideUI();

    // ���� UI ��������
    UUserWidget* GetCurrentUI() const { return CurrentUI; }

};
