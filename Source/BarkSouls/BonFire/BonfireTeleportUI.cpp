#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "UIManager.h"
#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::NativeConstruct()
{
    Super::NativeConstruct();

    // Stage 버튼 이벤트 바인딩
    if (Stage1Button)
    {
        ButtonStageMap.Add(Stage1Button, TEXT("Stage1"));
        Stage1Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    }

    if (Stage2Button)
    {
        ButtonStageMap.Add(Stage2Button, TEXT("Stage2"));
        Stage2Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    }
    if (Stage3Button)
    {
        ButtonStageMap.Add(Stage3Button, TEXT("Stage3"));
        Stage3Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    }
    if (BackButton) BackButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBackButtonClicked);

    CurrentStage = "";

    UIManager = Cast<AUIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AUIManager::StaticClass()));
}


void UBonfireTeleportUI::OnStageButtonClicked()
{   
    UButton* ClickedButton = nullptr;

    for (const TPair<UButton*, FName>& Pair : ButtonStageMap)
    {
        if (Pair.Key->HasKeyboardFocus())  // 현재 키보드 포커스를 가진 버튼 찾기
        {
            ClickedButton = Pair.Key;
            UE_LOG(LogTemp, Warning, TEXT("Button Clicked: %s"), *Pair.Value.ToString());
            break;
        }
    }

    // 버튼이 존재하면 해당 `StageName`을 찾아 실행
    if (ClickedButton && ButtonStageMap.Contains(ClickedButton))
    {
        UE_LOG(LogTemp, Warning, TEXT(" PopulateBonfireList "));
        FName StageName = ButtonStageMap[ClickedButton];
        PopulateBonfireList(StageName);
    }
}

void UBonfireTeleportUI::PopulateBonfireList(FName StageName)
{
    CurrentStage = StageName;
    UE_LOG(LogTemp, Warning, TEXT("Stage Name: %s"), *StageName.ToString());

    if (!BonfireList) return;

    BonfireList->ClearChildren();

    for (const TPair<FName, FBonfireData>& Pair : ABonfire::StaticActiveBonfires)
    {
        const FBonfireData& Bonfire = Pair.Value;

        // 현재 StageName과 일치하는 화톳불만 버튼 생성
        if (Bonfire.LevelName == StageName)
        {
            // 버튼 생성
            UButton* NewButton = NewObject<UButton>(this, UButton::StaticClass());
            if (!NewButton) continue;
            
            NewButton->SetVisibility(ESlateVisibility::Visible);
            NewButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBackButtonClicked);

            // 버튼 내부 UI 요소 생성
            UHorizontalBox* ButtonLayout = NewObject<UHorizontalBox>(this);

            // 이미지 추가
            UImage* ButtonImage = NewObject<UImage>(this);
            if (Bonfire.BonfireTexture)
            {
                ButtonImage->SetBrushFromTexture(Bonfire.BonfireTexture);
                ButtonImage->SetBrushSize(FVector2D(50.f, 50.f));
            }

            // 텍스트 추가
            UTextBlock* ButtonText = NewObject<UTextBlock>(this);
            ButtonText->SetText(FText::FromName(Bonfire.BonfireName));
            ButtonText->SetJustification(ETextJustify::Center);

            // UI 요소 배치
            ButtonLayout->AddChildToHorizontalBox(ButtonImage);
            ButtonLayout->AddChildToHorizontalBox(ButtonText);

            // 버튼에 배치 요소 적용
            NewButton->SetContent(ButtonLayout);

            // ScrollBox에 버튼 추가
            BonfireList->AddChild(NewButton);
            
        }
    }
}

void UBonfireTeleportUI::TeleportToBonfire(FName BonfireID)
{

}

void UBonfireTeleportUI::OnBackButtonClicked()
{
    if (UIManager)
    {
        UIManager->HideUI();
    }
}
