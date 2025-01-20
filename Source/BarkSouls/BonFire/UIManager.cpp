#include "UIManager.h"
#include "Kismet/GameplayStatics.h"

void UUIManager::Initialize(APlayerController* InPlayerController)
{
    // �÷��̾� ��Ʈ�ѷ� ����
    PlayerController = InPlayerController;
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UIManager: PlayerController is nullptr!"));
        return;
    }

    // TMap ��ȸ�ϸ� UI�� ���� �� �ʱ�ȭ
    for (const TPair<EUIType, TSubclassOf<UUserWidget>>& Pair : UIClassMap)
    {
        EUIType UIType = Pair.Key;
        TSubclassOf<UUserWidget> UIClass = Pair.Value;

        if (!UIClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("UIManager: UI Class for %d is nullptr!"), static_cast<int32>(UIType));
            continue;
        }

        // ���� ����
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerController, UIClass);
        if (NewWidget)
        {
            // Viewport�� �߰��ϰ� ���� ���·� ����
            NewWidget->AddToViewport();
            NewWidget->SetVisibility(ESlateVisibility::Hidden);

            // UIMap�� ����
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
    // ���� UI �����
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden);
        CurrentUI = nullptr;
    }
    else
    {
        // ���콺 Ŀ�� Ȱ��ȭ �� �Է� ��� ����
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;

            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputMode);
        }
    }

    // TMap���� UI �˻�
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
        CurrentUI->SetVisibility(ESlateVisibility::Hidden); // ���� UI ����
        CurrentUI = nullptr;

        // ���콺 Ŀ�� ��Ȱ��ȭ
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = false;

            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
        }

        UE_LOG(LogTemp, Log, TEXT("Current UI is now hidden."));
    }
}
