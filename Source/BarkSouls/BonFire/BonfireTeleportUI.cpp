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

    // 초기화 작업 (필요하면 작성)
}

void UBonfireTeleportUI::InitializeTeleportUI(const TMap<FName, FBonfireData>& ActiveBonfires)
{
    if (!BonfireList)
    {
        UE_LOG(LogTemp, Warning, TEXT("BonfireList is not bound!"));
        return;
    }

    BonfireList->ClearChildren(); // 기존 버튼 제거

    for (const TPair<FName, FBonfireData>& Bonfire : ActiveBonfires)
    {
        FName BonfireID = Bonfire.Key;
        const FBonfireData& Data = Bonfire.Value;

        // 버튼 생성
        UButton* NewButton = NewObject<UButton>(this);
        UTextBlock* ButtonLabel = NewObject<UTextBlock>(NewButton);

        // 버튼에 텍스트 추가
        ButtonLabel->SetText(FText::FromName(Data.BonfireName));
        NewButton->AddChild(ButtonLabel);

        // 버튼을 ScrollBox에 추가
        BonfireList->AddChild(NewButton);

        // Delegate 연결
        NewButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnBonfireClicked);

        // 버튼과 BonfireID 매핑
        ButtonIDMap.Add(NewButton, BonfireID);
    }
}

void UBonfireTeleportUI::OnBonfireClicked()
{
    //// 현재 클릭된 버튼 가져오기
    //UButton* ClickedButton = Cast<UButton>(GetOwningPlayer()->GetLastInputPressedWidget());
    //if (ClickedButton && ButtonIDMap.Contains(ClickedButton))
    //{
    //    FName BonfireID = ButtonIDMap[ClickedButton];

    //    // 화톳불 ID를 로그로 출력
    //    UE_LOG(LogTemp, Log, TEXT("Bonfire selected: %s"), *BonfireID.ToString());

    //    // 실제 동작 (예: 텔레포트) 추가
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
