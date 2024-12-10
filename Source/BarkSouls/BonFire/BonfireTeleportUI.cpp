#include "BonfireTeleportUI.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Bonfire.h"

void UBonfireTeleportUI::Initialize(ABonfire* InOwningBonfire)
{
    OwningBonfire = InOwningBonfire;
}

void UBonfireTeleportUI::NativeConstruct()
{
    Super::NativeConstruct();

    // ȭ��� ����Ʈ�� �ʱ�ȭ
    PopulateBonfireList();
}

void UBonfireTeleportUI::PopulateBonfireList()
{
    //if (!ScrollBox_BonfireList) return;

    //ScrollBox_BonfireList->ClearChildren(); // ���� �׸� ����

    //// Ȱ��ȭ�� ȭ��Ҹ� ��ȸ
    //for (const auto& Bonfire : ABonfire::BonfireLocations)
    //{
    //    if (Bonfire.Key.IsNone()) continue; // ��ȿ���� ���� ID�� ����

    //    // ��ư ����
    //    UButton* BonfireButton = NewObject<UButton>(this);
    //    UTextBlock* BonfireNameText = NewObject<UTextBlock>(this);

    //    // ��ư�� ȭ��� �̸� �߰�
    //    BonfireNameText->SetText(FText::FromName(Bonfire.Key));
    //    BonfireButton->AddChild(BonfireNameText);

    //    // Ŭ�� �̺�Ʈ �߰�
    //    FName BonfireID = Bonfire.Key; // ���� ������ ID ����
    //    BonfireButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::HandleBonfireClicked);

    //    // ScrollBox�� ��ư �߰�
    //    ScrollBox_BonfireList->AddChild(BonfireButton);
    //}
}

void UBonfireTeleportUI::HandleBonfireClicked(FName SelectedBonfireID)
{
    if (!OwningBonfire) return;

    // ���õ� ȭ��ҷ� ���� �̵�
    OwningBonfire->TeleportPlayer(SelectedBonfireID);

    // UI �ݱ�
    RemoveFromViewport();
}
