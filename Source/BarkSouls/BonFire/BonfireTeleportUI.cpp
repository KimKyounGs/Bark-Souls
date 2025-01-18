#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::InitializeUI(const TMap<FName, FBonfireData>& InActiveBonfires)
{
    // LevelBonfireMap �ʱ�ȭ
    LevelBonfireMap.Empty();

    // `TMap<FName, FBonfireData>`�� `TMap<FName, TArray<FBonfireData>>` �������� ��ȯ
    for (const TPair<FName, FBonfireData>& Pair : InActiveBonfires)
    {
        const FName& MapName = Pair.Value.MapName;
        if (!LevelBonfireMap.Contains(MapName))
        {
            LevelBonfireMap.Add(MapName, {});
        }
        
        LevelBonfireMap[MapName].Add(Pair.Value);
    }


    // Stage ��ư Ŭ�� �̺�Ʈ ����
    if (Stage1Button)
    {
        Stage1Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStage1ButtonClicked);
    }

    if (Stage2Button)
    {
        Stage2Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStage2ButtonClicked);
    }

    if (Stage3Button)
    {
        Stage3Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStage3ButtonClicked);
    }
}

void UBonfireTeleportUI::OnStage1ButtonClicked()
{
    if (LevelBonfireMap.Contains("Stage1"))
    {
        PopulateBonfireList(LevelBonfireMap["Stage1"]);
    }
}

void UBonfireTeleportUI::OnStage2ButtonClicked()
{
    if (LevelBonfireMap.Contains("Stage2"))
    {
        PopulateBonfireList(LevelBonfireMap["Stage2"]);
    }
}

void UBonfireTeleportUI::OnStage3ButtonClicked()
{
    if (LevelBonfireMap.Contains("Stage3"))
    {
        PopulateBonfireList(LevelBonfireMap["Stage3"]);
    }
}

void UBonfireTeleportUI::PopulateBonfireList(const TArray<FBonfireData>& Bonfires)
{
    BonfireList->ClearChildren(); // ���� ��ư ����

    for (const FBonfireData& Bonfire : Bonfires)
    {
        if (!Bonfire.bIsActivated)
        {
            continue; // Ȱ��ȭ���� ���� ȭ����� ����
        }

        // ��ư ����
        UButton* BonfireButton = NewObject<UButton>(this);
        UTextBlock* ButtonText = NewObject<UTextBlock>(BonfireButton);

        ButtonText->SetText(FText::FromName(Bonfire.BonfireName));
        BonfireButton->AddChild(ButtonText);

        BonfireList->AddChild(BonfireButton);

        // Delegate ���ε�
        BonfireButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBonfireButtonClicked);

        // ��ư�� BonfireID ����
        ButtonToBonfireIDMap.Add(BonfireButton, Bonfire.BonfireID);
    }
}

void UBonfireTeleportUI::OnBonfireButtonClicked()
{
    // Ŭ���� ��ư Ȯ��
    for (const TPair<UButton*, FName>& Pair : ButtonToBonfireIDMap)
    {
        if (Pair.Key->IsPressed()) // IsPressed()�� ���� ���� ��ư Ȯ��
        {
            FName BonfireID = Pair.Value;
            UE_LOG(LogTemp, Log, TEXT("Clicked Bonfire ID: %s"), *BonfireID.ToString());
            TeleportToBonfire(BonfireID); // BonfireID�� ����Ͽ� ���� ����
            return;
        }
    }
}

void UBonfireTeleportUI::TeleportToBonfire(FName BonfireID)
{
    for (const TPair<FName, TArray<FBonfireData>>& LevelData : LevelBonfireMap)
    {
        for (const FBonfireData& Bonfire : LevelData.Value)
        {
            if (Bonfire.BonfireID == BonfireID)
            {
                if (Bonfire.MapName != FName(*GetWorld()->GetMapName()))
                {
                    // ���� ����
                    UGameplayStatics::OpenLevel(this, Bonfire.MapName);
                }
                else
                {
                    // ���� �������� ��ġ �̵�
                    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
                    if (PlayerController && PlayerController->GetPawn())
                    {
                        PlayerController->GetPawn()->SetActorTransform(Bonfire.BonfireTransform);
                    }
                }

                return;
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Bonfire ID not found: %s"), *BonfireID.ToString());
}