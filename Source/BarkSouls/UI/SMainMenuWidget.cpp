// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "SlateBasics.h" // Slate�� �⺻���� ���� ����
#include "SlateExtras.h" // Sltae�� �߰����� Ȯ�� ���
#include "SlateOptMacros.h" // Slate UI�� ����ȭ�� ���� ��ũ�θ� �����ϴ� ��� -> Construct ��ũ�� ��� ����
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h" 
#include "BarkSouls/BarkSoulsGameInstance.h"
#include "Widgets/Text/STextBlock.h" // Slate UI���� �ؽ�Ʈ�� ǥ���ϴ� ����
#include "Widgets/Input/SButton.h" // Slate UI���� ��ư�� �����ϴ� ����
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"



#define LOCTEXT_NAMESPACE "MainMenu" // LOCTEXT() ���� �ٱ��� ������ ���� LOCTEXT�� ����� �� �ʿ�

// BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION  // Slate UI ���� ����ȭ ����
void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	FSlateFontInfo ButtonFont = FCoreStyle::Get().GetFontStyle("NormalText");
	ButtonFont.Size = 32;

	ChildSlot
	[
		// ȭ�� ��ü�� ���� SOverlay
		SNew(SOverlay)

		// ���� ���� ��ư
		+ SOverlay::Slot()
		.HAlign(HAlign_Left) // ���� ����
		.VAlign(VAlign_Center) // ��ư�� ���� �߾� ����
		.Padding(FMargin(50, 0)) // ���ʿ��� 50px ���������� �е� ����
		[
			SNew(SBorder) // ��ư���� ���δ� �ڽ�
			.BorderBackgroundColor(FLinearColor(0,0,0,0.5))
			.Padding(20) // �ڽ� ���� ����
			[
				SNew(SBox)
				.WidthOverride(300) // �ڽ� �ʺ�
				.HeightOverride(400) // �ڽ� ����
				[
					SNew(SVerticalBox)

					// ���� ���� ��ư
					+ SVerticalBox::Slot()
					.Padding(10)
					.AutoHeight()
					[
						SNew(SBox)
						.WidthOverride(250)
						.HeightOverride(80)
						[
							SNew(SButton) // ��ư ����
							.HAlign(HAlign_Center)
							.TextStyle(FCoreStyle::Get(), "NormalText") // �⺻ ��Ÿ�� ����
							.OnClicked(this, &SMainMenuWidget::OnStartGameClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("StartGame", "StartGame")) // ��ư�� �ؽ�Ʈ ǥ��
								.Font(ButtonFont)// ��Ʈ ũ�� ����
							]
						]
					]


					// �ɼ� ��ư
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

					// ���� ���� ��ư
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
								.Font(ButtonFont) // ��Ʈ ũ�� ����
							]
						]
					]
				]
			
			]

		]
	];
	
}
// END_SLATE_FUNCTION_BUILD_OPTIMIZATION // Slate UI ���� ����ȭ ����
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
		// UI ���� (���� Slate UI�� Viewport���� ����)
		GEngine->GameViewport->RemoveViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(SharedThis(this)));

		// �Է� ��带 ���� �������� ����
		APlayerController* PC = GEngine->GameViewport->GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = false; // ���콺 Ŀ�� ����
			PC->SetInputMode(FInputModeGameOnly()); // ���� �Է� ���� ����
		}

		// ���� �̵�
		UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), "TestLevel2");
	}
	return FReply::Handled();
}

FReply SMainMenuWidget::OnSettingsClicked()
{
	// TODO: ���� �޴� ����
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

