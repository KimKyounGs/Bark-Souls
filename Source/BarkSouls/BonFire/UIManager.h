// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
 * UIManager : UI를 중앙에서 관리하는 클래스
 */
UCLASS()
class BARKSOULS_API UUIManager : public UObject
{
	GENERATED_BODY()
private:
    // 현재 활성화된 UI
    UPROPERTY(EditAnywhere)
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

    // Initialize 함수
    void Initialize(APlayerController* InPlayerController);

    // UI 상태 전환
    void ShowUI(EUIType UIType);

    // 현재 활성화된 UI 숨기기
    void HideUI();

    // 현재 UI 가져오기
    UUserWidget* GetCurrentUI() const { return CurrentUI; }

};
