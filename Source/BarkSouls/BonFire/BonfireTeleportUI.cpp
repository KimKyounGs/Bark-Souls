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

    // 화톳불 리스트를 초기화
    PopulateBonfireList();
}

void UBonfireTeleportUI::PopulateBonfireList()
{
    //if (!ScrollBox_BonfireList) return;

    //ScrollBox_BonfireList->ClearChildren(); // 기존 항목 제거

    //// 활성화된 화톳불만 순회
    //for (const auto& Bonfire : ABonfire::BonfireLocations)
    //{
    //    if (Bonfire.Key.IsNone()) continue; // 유효하지 않은 ID는 무시

    //    // 버튼 생성
    //    UButton* BonfireButton = NewObject<UButton>(this);
    //    UTextBlock* BonfireNameText = NewObject<UTextBlock>(this);

    //    // 버튼에 화톳불 이름 추가
    //    BonfireNameText->SetText(FText::FromName(Bonfire.Key));
    //    BonfireButton->AddChild(BonfireNameText);

    //    // 클릭 이벤트 추가
    //    FName BonfireID = Bonfire.Key; // 로컬 변수로 ID 저장
    //    BonfireButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::HandleBonfireClicked);

    //    // ScrollBox에 버튼 추가
    //    ScrollBox_BonfireList->AddChild(BonfireButton);
    //}
}

void UBonfireTeleportUI::HandleBonfireClicked(FName SelectedBonfireID)
{
    if (!OwningBonfire) return;

    // 선택된 화톳불로 순간 이동
    OwningBonfire->TeleportPlayer(SelectedBonfireID);

    // UI 닫기
    RemoveFromViewport();
}
