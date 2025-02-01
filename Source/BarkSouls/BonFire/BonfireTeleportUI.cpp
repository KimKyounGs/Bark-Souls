#include "BonfireTeleportUI.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::NativeConstruct()
{
    Super::NativeConstruct();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    DogController = Cast<ADogCharacterController>(PlayerController);

    // Stage 버튼 이벤트 바인딩
    if (Stage1Button) Stage1Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    if (Stage2Button) Stage2Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    if (Stage3Button) Stage3Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
    if (BackButton) BackButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBackButtonClicked);

    CurrentStage = "";
}


void UBonfireTeleportUI::OnStageButtonClicked()
{   
    UButton* NewButton = NewObject<UButton>(this, UButton::StaticClass()); 

    if (NewButton)
    {
        NewButton->SetVisibility(ESlateVisibility::Visible);

        NewButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBackButtonClicked);

        UTextBlock* ButtonText = NewObject<UTextBlock>(this);
        ButtonText->SetText(FText::FromString(TEXT("New Button")));
        ButtonText->SetJustification(ETextJustify::Center);

        // 버튼에 텍스트를 추가하려면 UButton 자체로는 안 되고, UWidget을 추가해야 함.
        UVerticalBox* ButtonContainer = NewObject<UVerticalBox>(this);
        ButtonContainer->AddChildToVerticalBox(ButtonText);
        NewButton->AddChild(ButtonContainer);

        // ScrollBox에 버튼 추가
        BonfireList->AddChild(NewButton);
    }
}

void UBonfireTeleportUI::PopulateBonfireList(FName StageName)
{
    CurrentStage = StageName;
}

void UBonfireTeleportUI::TeleportToBonfire(FName BonfireID)
{

}

void UBonfireTeleportUI::OnBackButtonClicked()
{
    if (DogController)
    {
        AUIManager* UIManager = DogController->GetUIManager();
        if (UIManager)
        {
            UIManager->ShowUI(EUIType::BonfireUI);
        }
    }
}
