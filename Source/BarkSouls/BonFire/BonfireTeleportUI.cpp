#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::InitializeUI(const TMap<FName, FBonfireData>& InActiveBonfires)
{
    // LevelBonfireMap 초기화
    LevelBonfireMap.Empty();

    // `TMap<FName, FBonfireData>`를 `TMap<FName, TArray<FBonfireData>>` 형식으로 변환
    for (const TPair<FName, FBonfireData>& Pair : InActiveBonfires)
    {
        const FName& MapName = Pair.Value.MapName;
        if (!LevelBonfireMap.Contains(MapName))
        {
            LevelBonfireMap.Add(MapName, {});
        }
        
        LevelBonfireMap[MapName].Add(Pair.Value);
    }


    // Stage 버튼 클릭 이벤트 연결
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
    BonfireList->ClearChildren(); // 기존 버튼 제거

    for (const FBonfireData& Bonfire : Bonfires)
    {
        if (!Bonfire.bIsActivated)
        {
            continue; // 활성화되지 않은 화톳불은 무시
        }

        // 버튼 생성
        UButton* BonfireButton = NewObject<UButton>(this);
        UTextBlock* ButtonText = NewObject<UTextBlock>(BonfireButton);

        ButtonText->SetText(FText::FromName(Bonfire.BonfireName));
        BonfireButton->AddChild(ButtonText);

        BonfireList->AddChild(BonfireButton);

        // Delegate 바인딩
        BonfireButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBonfireButtonClicked);

        // 버튼과 BonfireID 매핑
        ButtonToBonfireIDMap.Add(BonfireButton, Bonfire.BonfireID);
    }
}

void UBonfireTeleportUI::OnBonfireButtonClicked()
{
    // 클릭된 버튼 확인
    for (const TPair<UButton*, FName>& Pair : ButtonToBonfireIDMap)
    {
        if (Pair.Key->IsPressed()) // IsPressed()로 현재 눌린 버튼 확인
        {
            FName BonfireID = Pair.Value;
            UE_LOG(LogTemp, Log, TEXT("Clicked Bonfire ID: %s"), *BonfireID.ToString());
            TeleportToBonfire(BonfireID); // BonfireID를 사용하여 동작 실행
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
                    // 레벨 변경
                    UGameplayStatics::OpenLevel(this, Bonfire.MapName);
                }
                else
                {
                    // 같은 레벨에서 위치 이동
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