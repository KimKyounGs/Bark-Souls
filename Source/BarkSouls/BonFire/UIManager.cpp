#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AUIManager::AUIManager()
{
    // Tick을 사용하지 않음
    PrimaryActorTick.bCanEverTick = false;
}

void AUIManager::BeginPlay()
{
    Super::BeginPlay();

    // 플레이어 컨트롤러 가져오기
    PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UIManager: PlayerController is nullptr!"));
        return;
    }

    // UIClassMap을 순회하며 UI를 생성
    for (const TPair<EUIType, TSubclassOf<UUserWidget>>& Pair : UIClassMap)
    {
        EUIType UIType = Pair.Key;
        TSubclassOf<UUserWidget> UIClass = Pair.Value;

        if (!UIClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("UIManager: UI Class for %d is nullptr!"), static_cast<int32>(UIType));
            continue;
        }

        // UI 위젯 생성
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerController, UIClass);
        if (NewWidget)
        {
            // Viewport에 추가하고 숨김 상태로 설정
            NewWidget->AddToViewport();
            NewWidget->SetVisibility(ESlateVisibility::Hidden);

            // UIMap에 추가
            UIMap.Add(UIType, NewWidget);

            UE_LOG(LogTemp, Log, TEXT("UIManager: Successfully created and added UI %d to UIMap."), static_cast<int32>(UIType));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UIManager: Failed to create UI %d"), static_cast<int32>(UIType));
        }
    }
}

void AUIManager::ShowUI(EUIType UIType)
{
    // 현재 UI 숨기기
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden);
        CurrentUI = nullptr;
    }

    // TMap에서 UI 검색
    if (UIMap.Contains(UIType))
    {
        UUserWidget* TargetUI = UIMap[UIType];
        if (TargetUI)
        {
            TargetUI->SetVisibility(ESlateVisibility::Visible);
            CurrentUI = TargetUI;

            // 마우스 커서 활성화 및 입력 모드 전환
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;

                FInputModeUIOnly InputMode;
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            UE_LOG(LogTemp, Log, TEXT("UIManager: UI %d is now visible"), static_cast<int32>(UIType));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UIManager: UI %d not found in UIMap!"), static_cast<int32>(UIType));
    }
}

void AUIManager::HideUI()
{
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden);
        CurrentUI = nullptr;

        // 마우스 커서 비활성화
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = false;

            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
        }

        UE_LOG(LogTemp, Log, TEXT("UIManager: Current UI is now hidden."));
    }
}
