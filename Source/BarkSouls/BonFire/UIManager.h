#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
 * UIManager : UI�� �߾ӿ��� �����ϴ� ����
 */
UCLASS()
class BARKSOULS_API AUIManager : public AActor
{
    GENERATED_BODY()

private:
    // ���� Ȱ��ȭ�� UI
    UPROPERTY()
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

    // ������
    AUIManager();

protected:
    // ������ �����ֱ� �Լ� (�ʱ�ȭ)
    virtual void BeginPlay() override;

public:
    // Ư�� UI Ȱ��ȭ
    void ShowUI(EUIType UIType);

    // ���� Ȱ��ȭ�� UI �����
    void HideUI();

    // ���� UI ��������
    UUserWidget* GetCurrentUI() const { return CurrentUI; }
};
