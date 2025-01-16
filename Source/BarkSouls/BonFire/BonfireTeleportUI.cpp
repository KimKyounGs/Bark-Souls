// Fill out your copyright notice in the Description page of Project Settings.

#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"

void UBonfireTeleportUI::NativeConstruct()
{
    Super::NativeConstruct();

    // �ʱ�ȭ �۾� (�ʿ��ϸ� �ۼ�)
}

void UBonfireTeleportUI::InitializeTeleportUI(const TMap<FName, FBonfireData>& ActiveBonfires)
{
    if (!BonfireList)
    {
        UE_LOG(LogTemp, Warning, TEXT("BonfireList is not bound!"));
        return;
    }

    BonfireList->ClearChildren(); // ���� ��ư ����

    for (const TPair<FName, FBonfireData>& Bonfire : ActiveBonfires)
    {
        FName BonfireID = Bonfire.Key;
        const FBonfireData& Data = Bonfire.Value;

        // ��ư ����
        UButton* NewButton = NewObject<UButton>(this);
        UTextBlock* ButtonLabel = NewObject<UTextBlock>(NewButton);

        // ��ư�� �ؽ�Ʈ �߰�
        ButtonLabel->SetText(FText::FromName(Data.BonfireName));
        NewButton->AddChild(ButtonLabel);

        // ��ư�� ScrollBox�� �߰�
        BonfireList->AddChild(NewButton);

        // Delegate ����
        NewButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBonfireClicked);

        // ��ư�� BonfireID ����
        ButtonIDMap.Add(NewButton, BonfireID);
    }
}

void UBonfireTeleportUI::OnBonfireClicked()
{
    //// ���� Ŭ���� ��ư ��������
    //UButton* ClickedButton = Cast<UButton>(GetOwningPlayer()->GetLastInputPressedWidget());
    //if (ClickedButton && ButtonIDMap.Contains(ClickedButton))
    //{
    //    FName BonfireID = ButtonIDMap[ClickedButton];

    //    // ȭ��� ID�� �α׷� ���
    //    UE_LOG(LogTemp, Log, TEXT("Bonfire selected: %s"), *BonfireID.ToString());

    //    // ���� ���� (��: �ڷ���Ʈ) �߰�
    //    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    //    if (PlayerController)
    //    {
    //        ABonfire* BonfireActor = Cast<ABonfire>(PlayerController->GetPawn());
    //        if (BonfireActor)
    //        {
    //            BonfireActor->TeleportPlayer(BonfireID);
    //        }
    //    }
    //}
}
