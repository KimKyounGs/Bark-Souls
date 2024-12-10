#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireTeleportUI.generated.h"

/**
 * 화톳불 전송 UI 클래스
 */
UCLASS()
class BARKSOULS_API UBonfireTeleportUI : public UUserWidget
{
    GENERATED_BODY()

private:
    // ScrollBox: 활성화된 화톳불 리스트 표시
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* ScrollBox_BonfireList;

    // 부모 화톳불 객체
    class ABonfire* OwningBonfire;

public:
    // OwningBonfire를 설정
    void Initialize(ABonfire* InOwningBonfire);

    // UI를 채우는 함수
    void PopulateBonfireList();

protected:
    // UI 생성 시 초기화
    virtual void NativeConstruct() override;

    // 화톳불 선택 시 호출
    UFUNCTION()
    void HandleBonfireClicked(FName SelectedBonfireID);
};
