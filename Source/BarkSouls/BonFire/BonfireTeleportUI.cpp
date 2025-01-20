#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::InitializeUI(const TMap<FName, FBonfireData>& InActiveBonfires)
{
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
    return;
}

void UBonfireTeleportUI::OnStage2ButtonClicked()
{
    return;
}

void UBonfireTeleportUI::OnStage3ButtonClicked()
{
    return;
}
