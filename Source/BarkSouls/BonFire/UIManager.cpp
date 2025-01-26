#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AUIManager::AUIManager()
{
    // Tick�� ������� ����
    PrimaryActorTick.bCanEverTick = false;
}

void AUIManager::BeginPlay()
{
    Super::BeginPlay();

    // �÷��̾� ��Ʈ�ѷ� ��������
    PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UIManager: PlayerController is nullptr!"));
        return;
    }

    // UIClassMap�� ��ȸ�ϸ� UI�� ����
    for (const TPair<EUIType, TSubclassOf<UUserWidget>>& Pair : UIClassMap)
    {
        EUIType UIType = Pair.Key;
        TSubclassOf<UUserWidget> UIClass = Pair.Value;

        if (!UIClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("UIManager: UI Class for %d is nullptr!"), static_cast<int32>(UIType));
            continue;
        }

        // UI ���� ����
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(PlayerController, UIClass);
        if (NewWidget)
        {
            // Viewport�� �߰��ϰ� ���� ���·� ����
            NewWidget->AddToViewport();
            NewWidget->SetVisibility(ESlateVisibility::Hidden);

            // UIMap�� �߰�
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
    // ���� UI �����
    if (CurrentUI)
    {
        CurrentUI->SetVisibility(ESlateVisibility::Hidden);
        CurrentUI = nullptr;
    }

    // TMap���� UI �˻�
    if (UIMap.Contains(UIType))
    {
        UUserWidget* TargetUI = UIMap[UIType];
        if (TargetUI)
        {
            TargetUI->SetVisibility(ESlateVisibility::Visible);
            CurrentUI = TargetUI;

            // ���콺 Ŀ�� Ȱ��ȭ �� �Է� ��� ��ȯ
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

        // ���콺 Ŀ�� ��Ȱ��ȭ
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = false;

            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
        }

        UE_LOG(LogTemp, Log, TEXT("UIManager: Current UI is now hidden."));
    }
}
