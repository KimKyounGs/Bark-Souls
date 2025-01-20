#include "UIManager.h"
#include "Kismet/GameplayStatics.h"

void UUIManager::Initialize(APlayerController* InPlayerController)
{
    // 플레이어 컨트롤러 설정
    PlayerController = InPlayerController;
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UIManager: PlayerController is nullptr!"));
        return;
    }

    // TMap 순회하며 UI를 생성 및 초기화
    for (const TPair<EUIType, TSubclassOf<UUserWidget>>& Pair : UIClassMap)
    {
        EUIType UIType = Pair.Key;
        TSubclassOf<UUserWidget> UIClass = Pair.Value;

        if (!UIClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("UIManager: UI Class for %d is nullptr!"), static_cast<int32>(UIType));
            continue;
        }

        // 위젯 생성
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerController, UIClass);
        if (NewWidget)
        {
            // Viewport에 추가하고 숨김 상태로 설정
            NewWidget->AddToViewport();
            NewWidget->SetVisibility(ESlateVisibility::Hidden);

            // UIMap에 저장
            UIMap.Add(UIType, NewWidget);

            UE_LOG(LogTemp, Log, TEXT("UIManager: Successfully created and added UI %d to UIMap."), static_cast<int32>(UIType));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UIManager: Failed to create UI %d"), static_cast<int32>(UIType));
        }
    }
}

void UUIManager::ShowUI(EUIType UIType)
{
    // 현재 UI 숨기기
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden);
        CurrentUI = nullptr;
    }
    else
    {
        // 마우스 커서 활성화 및 입력 모드 변경
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;

            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputMode);
        }
    }

    // TMap에서 UI 검색
    if (UIMap.Contains(UIType))
    {
        UUserWidget* TargetUI = UIMap[UIType];
        if (TargetUI)
        {
            TargetUI->SetVisibility(ESlateVisibility::Visible);
            CurrentUI = TargetUI;
            UE_LOG(LogTemp, Log, TEXT("UIManager: UI %d is now visible"), static_cast<int32>(UIType));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UIManager: UI %d not found in UIMap!"), static_cast<int32>(UIType));
    }
}


void UUIManager::HideUI()
{
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden); // 현재 UI 숨김
        CurrentUI = nullptr;

        // 마우스 커서 비활성화
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = false;

            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
        }

        UE_LOG(LogTemp, Log, TEXT("Current UI is now hidden."));
    }
}
