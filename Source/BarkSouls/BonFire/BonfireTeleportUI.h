#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireTeleportUI.generated.h"

/**
 * ȭ��� ���� UI Ŭ����
 */
UCLASS()
class BARKSOULS_API UBonfireTeleportUI : public UUserWidget
{
    GENERATED_BODY()

private:
    // ScrollBox: Ȱ��ȭ�� ȭ��� ����Ʈ ǥ��
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* ScrollBox_BonfireList;

    // �θ� ȭ��� ��ü
    class ABonfire* OwningBonfire;

public:
    // OwningBonfire�� ����
    void Initialize(ABonfire* InOwningBonfire);

    // UI�� ä��� �Լ�
    void PopulateBonfireList();

protected:
    // UI ���� �� �ʱ�ȭ
    virtual void NativeConstruct() override;

    // ȭ��� ���� �� ȣ��
    UFUNCTION()
    void HandleBonfireClicked(FName SelectedBonfireID);
};
