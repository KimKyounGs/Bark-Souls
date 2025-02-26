// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "SlateBasics.h" // Slate의 기본적인 위젯 포함
#include "SlateExtras.h" // Sltae의 추가적인 확장 기능
#include "SlateOptMacros.h" // Slate UI의 최적화를 위한 매크로를 포함하는 헤더 -> Construct 매크로 사용 가능
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h" 
#include "Widgets/Text/STextBlock.h" // Slate UI에서 텍스트를 표시하는 위젯
#include "Widgets/Input/SButton.h" // Slate UI에서 버튼을 생성하는 위젯

#define LOCTEXT_NAMESPACE "MainMenu" // LOCTEXT() 같은 다국어 지원을 위한 LOCTEXT를 사용할 때 필요

// BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION  // Slate UI 생성 최적화 시작
void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SVerticalBox)

		// 게임 시작 버튼
		+ SVerticalBox::Slot() // SVerticalBox안에 새로운 UI 요소 추가
		.Padding(10) // 버튼 주변에 10px 간격 추가
		.VAlign(VAlign_Center) // 버튼을 수직 중앙 정렬
		[
			SNew(SButton) // 버튼 생성
			.Text(LOCTEXT("StartGame", "GameStart")) // 버튼에 텍스트 표시
			.OnClicked(this, &SMainMenuWidget::OnStartGameClicked) 
		]


		// 설정 버튼
		+ SVerticalBox::Slot()
		.Padding(10)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(LOCTEXT("Settings", "Option"))
			.OnClicked(this, &SMainMenuWidget::OnSettingsClicked)
		]

		
		// 게임 종료 버튼
		+ SVerticalBox::Slot()
		.Padding(10)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(LOCTEXT("QuitGame", "Exit"))
			.OnClicked(this, &SMainMenuWidget::OnQuitGameClicked)
		]
	];
	
}
// END_SLATE_FUNCTION_BUILD_OPTIMIZATION // Slate UI 생성 최적화 종료
#undef LOCTEXT_NAMESPACE


FReply SMainMenuWidget::OnStartGameClicked()
{
	if (GEngine && GEngine->GameViewport)
	{
		UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), "TestLevel1");
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

