#include "BonfireTeleportUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UIManager.h"
#include "BarkSouls/BarkSoulsGameInstance.h"


void UBonfireTeleportUI::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<UBarkSoulsGameInstance>(UGameplayStatics::GetGameInstance(this));

	// Stage 버튼 이벤트 바인딩
	if (Stage1Button)
	{
		ButtonStageMap.Add(Stage1Button, TEXT("TestLevel1"));
		Stage1Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
	}

	if (Stage2Button)
	{
		ButtonStageMap.Add(Stage2Button, TEXT("TestLevel2"));
		Stage2Button->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnStageButtonClicked);
	}
	if (Stage3Button)
	{
		ButtonStageMap.Add(Stage3Button, TEXT("TestLevel3"));
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
			break;
		}
	}

	// 버튼이 존재하면 해당 `StageName`을 찾아 실행
	if (ClickedButton && ButtonStageMap.Contains(ClickedButton))
	{
		FName StageName = ButtonStageMap[ClickedButton];
		PopulateBonfireList(StageName);
	}
}

void UBonfireTeleportUI::PopulateBonfireList(FName StageName)
{
	CurrentStage = StageName;

	if (!BonfireScrollBox || !BonfireWrapBox) return;

	// 기존 버튼 삭제
	BonfireWrapBox->ClearChildren();

	for (const TPair<FName, FBonfireData>& Pair : GameInstance->BonfireMap)
	{
		const FBonfireData& Bonfire = Pair.Value;
		// 현재 스테이지와 일치하는 화톳불만 추가
		if (Bonfire.LevelName != StageName) continue;

		// 1.버튼 생성
		UButton* NewButton = NewObject<UButton>(this, UButton::StaticClass());
		if (!NewButton) continue;

		NewButton->SetVisibility(ESlateVisibility::Visible);
		// 버튼과 BonfireID를 매핑
		ButtonBonfireMap.Add(NewButton, Bonfire.BonfireID);
		NewButton->OnClicked.AddDynamic(this, &UBonfireTeleportUI::OnAnyBonfireButtonClicked);

		// 2.버튼 내부 UI 요소 생성 -> (가로 정렬을 하기 위해서 UHorizontalBox 사용)
		UHorizontalBox* ButtonLayout = NewObject<UHorizontalBox>(this);

		// 3.이미지 추가
		UImage* ButtonImage = NewObject<UImage>(this);
		if (Bonfire.BonfireTexture)
		{
			ButtonImage->SetBrushFromTexture(Bonfire.BonfireTexture);
			ButtonImage->SetBrushSize(FVector2D(300.f, 300.f));
		}

		// 4.텍스트 추가
		UTextBlock* ButtonText = NewObject<UTextBlock>(this);
		ButtonText->SetText(FText::FromName(Bonfire.BonfireName));
		ButtonText->SetJustification(ETextJustify::Center);
		// ButtonText->SetWrapTextAt(180.f);

		// 5.UI 요소 배치
		ButtonLayout->AddChildToHorizontalBox(ButtonImage);
		ButtonLayout->AddChildToHorizontalBox(ButtonText);
		NewButton->SetContent(ButtonLayout);

		// 6. 버튼을 UWrapBox에 추가하여 자동 정렬 (한 줄에 5개씩 배치)
		UWrapBoxSlot* WrapSlot = BonfireWrapBox->AddChildToWrapBox(NewButton);
		if (WrapSlot)
		{
			WrapSlot->SetPadding(FMargin(10.f)); // 버튼 간에 간격 조정
			WrapSlot->SetHorizontalAlignment(HAlign_Center);
		}
	}

	// 7. `ScrollBox`가 `WrapBox`를 포함하도록 설정
	BonfireScrollBox->ClearChildren();
	BonfireScrollBox->AddChild(BonfireWrapBox);
}

void UBonfireTeleportUI::OnAnyBonfireButtonClicked()
{
	UButton* ClickedButton = nullptr;

	// 클릭된 버튼을 찾아야 함
	for (const TPair<UButton*, FName>& Pair : ButtonBonfireMap)
	{
		if (Pair.Key->HasKeyboardFocus())  // 현재 클릭된 버튼 감지
		{
			ClickedButton = Pair.Key;
			break;
		}
	}

	// 버튼이 존재하면 해당 BonfireID로 이동
	if (ClickedButton && ButtonBonfireMap.Contains(ClickedButton))
	{
		FName BonfireID = ButtonBonfireMap[ClickedButton];
		TeleportToBonfire(BonfireID);
	}
}

void UBonfireTeleportUI::TeleportToBonfire(FName BonfireID)
{
	if (!GameInstance->BonfireMap.Contains(BonfireID)) return;

	const FBonfireData& Bonfire = GameInstance->BonfireMap[BonfireID];

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
	if (!PlayerCharacter) return;
	// 같은 레벨이면 위치 이동, 다른 레벨이면 레벨 변경
	if (Bonfire.LevelName == UGameplayStatics::GetCurrentLevelName(GetWorld()))
	{
		UIManager->HideUI();
		// 같은 레벨이면 위치 이동
		PlayerCharacter->SetActorLocation(Bonfire.BonfireTransform.GetLocation());
	}
	else
	{
		// 다른 레벨이면 이동할 화톳불 정보 저장 후 레벨 변경
		GameInstance->SetSelectedBonfire(BonfireID);
		UIManager->HideUI();
		UGameplayStatics::OpenLevel(GetWorld(), Bonfire.LevelName);
	}
}

void UBonfireTeleportUI::OnBackButtonClicked()
{
	if (UIManager)
	{
		UIManager->HideUI();
	}
}
