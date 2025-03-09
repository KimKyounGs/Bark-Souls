// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "SlateBasics.h" // Slate의 기본적인 위젯 포함
#include "SlateExtras.h" // Sltae의 추가적인 확장 기능
#include "SlateOptMacros.h" // Slate UI의 최적화를 위한 매크로를 포함하는 헤더 -> Construct 매크로 사용 가능
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h" 
#include "BarkSouls/BarkSoulsGameInstance.h"
#include "Widgets/Text/STextBlock.h" // Slate UI에서 텍스트를 표시하는 위젯
#include "Widgets/Input/SButton.h" // Slate UI에서 버튼을 생성하는 위젯
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"



#define LOCTEXT_NAMESPACE "MainMenu" // LOCTEXT() 같은 다국어 지원을 위한 LOCTEXT를 사용할 때 필요

// BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION  // Slate UI 생성 최적화 시작
void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	FSlateFontInfo ButtonFont = FCoreStyle::Get().GetFontStyle("NormalText");
	ButtonFont.Size = 32;

	ChildSlot
	[
		// 화면 전체를 덮는 SOverlay
		SNew(SOverlay)

		// 게임 시작 버튼
		+ SOverlay::Slot()
		.HAlign(HAlign_Left) // 왼쪽 정렬
		.VAlign(VAlign_Center) // 버튼을 수직 중앙 정렬
		.Padding(FMargin(50, 0)) // 왼쪽에서 50px 떨어지도록 패딩 설정
		[
			SNew(SBorder) // 버튼들을 감싸는 박스
			.BorderBackgroundColor(FLinearColor(0,0,0,0.5))
			.Padding(20) // 박스 내부 여백
			[
				SNew(SBox)
				.WidthOverride(300) // 박스 너비
				.HeightOverride(400) // 박스 높이
				[
					SNew(SVerticalBox)

					// 게임 시작 버튼
					+ SVerticalBox::Slot()
					.Padding(10)
					.AutoHeight()
					[
						SNew(SBox)
						.WidthOverride(250)
						.HeightOverride(80)
						[
							SNew(SButton) // 버튼 생성
							.HAlign(HAlign_Center)
							.TextStyle(FCoreStyle::Get(), "NormalText") // 기본 스타일 적용
							.OnClicked(this, &SMainMenuWidget::OnStartGameClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("StartGame", "StartGame")) // 버튼에 텍스트 표시
								.Font(ButtonFont)// 폰트 크기 적용
							]
						]
					]


					// 옵션 버튼
					+ SVerticalBox::Slot()
					.Padding(10)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(250)
						.HeightOverride(80)
						[
							SNew(SButton)
							.HAlign(HAlign_Center)
							.OnClicked(this, &SMainMenuWidget::OnSettingsClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Settings", "Settings"))
								.Font(ButtonFont)
							]
						]
					]

					// 게임 종료 버튼
					+ SVerticalBox::Slot()
					.Padding(10)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(250)
						.HeightOverride(80)
						[
							SNew(SButton)
							.HAlign(HAlign_Center)
							.OnClicked(this, &SMainMenuWidget::OnQuitGameClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("QuitGame", "QuitGame"))
								.Font(ButtonFont) // 폰트 크기 적용
							]
						]
					]
				]
			
			]

		]
	];
	
}
// END_SLATE_FUNCTION_BUILD_OPTIMIZATION // Slate UI 생성 최적화 종료
#undef LOCTEXT_NAMESPACE


FReply SMainMenuWidget::OnStartGameClicked()
{
	if (GEngine && GEngine->GameViewport)
	{
		UBarkSoulsGameInstance* MyGameInstance = Cast<UBarkSoulsGameInstance>(GEngine->GameViewport->GetWorld()->GetGameInstance());
		if (MyGameInstance)
		{
			MyGameInstance->bIsMainMenuActive = false;
		}
		// UI 제거 (현재 Slate UI를 Viewport에서 삭제)
		GEngine->GameViewport->RemoveViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(SharedThis(this)));

		// 입력 모드를 게임 전용으로 변경
		APlayerController* PC = GEngine->GameViewport->GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = false; // 마우스 커서 숨김
			PC->SetInputMode(FInputModeGameOnly()); // 게임 입력 모드로 변경
		}

		// 레벨 이동
		UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), "TestLevel2");
	}
	return FReply::Handled();
}

FReply SMainMenuWidget::OnSettingsClicked()
{
	// TODO: 설정 메뉴 열기
	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitGameClicked()
{
	if (GEngine && GEngine->GameViewport)
	{
		UKismetSystemLibrary::QuitGame(GEngine->GameViewport->GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
	return FReply::Handled();
}

