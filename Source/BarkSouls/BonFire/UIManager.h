#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

/**
 * UI Enum 정의 : UI 이름을 Enum으로 관리
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
 * UIManager : UI를 중앙에서 관리하는 액터
 */
UCLASS()
class BARKSOULS_API AUIManager : public AActor
{
    GENERATED_BODY()

private:
    // 현재 활성화된 UI
    UPROPERTY()
    UUserWidget* CurrentUI;

    // 모든 UI를 관리하는 TMap
    UPROPERTY()
    TMap<EUIType, UUserWidget*> UIMap;

    // 플레이어 컨트롤러
    UPROPERTY()
    class APlayerController* PlayerController;

public:
    // 에디터에서 설정 가능한 UI 클래스 맵
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TMap<EUIType, TSubclassOf<UUserWidget>> UIClassMap;

    // 생성자
    AUIManager();

protected:
    // 액터의 생명주기 함수 (초기화)
    virtual void BeginPlay() override;

public:
    // 특정 UI 활성화
    void ShowUI(EUIType UIType);

    // 현재 활성화된 UI 숨기기
    void HideUI();

    // 현재 UI 가져오기
    UUserWidget* GetCurrentUI() const { return CurrentUI; }
};
