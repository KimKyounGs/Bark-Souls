// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "SlateBasics.h" // Slate�� �⺻���� ���� ����
#include "SlateExtras.h" // Sltae�� �߰����� Ȯ�� ���
#include "SlateOptMacros.h" // Slate UI�� ����ȭ�� ���� ��ũ�θ� �����ϴ� ��� -> Construct ��ũ�� ��� ����
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h" 
#include "Widgets/Text/STextBlock.h" // Slate UI���� �ؽ�Ʈ�� ǥ���ϴ� ����
#include "Widgets/Input/SButton.h" // Slate UI���� ��ư�� �����ϴ� ����

#define LOCTEXT_NAMESPACE "MainMenu" // LOCTEXT() ���� �ٱ��� ������ ���� LOCTEXT�� ����� �� �ʿ�

// BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION  // Slate UI ���� ����ȭ ����
void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SVerticalBox)

		// ���� ���� ��ư
		+ SVerticalBox::Slot() // SVerticalBox�ȿ� ���ο� UI ��� �߰�
		.Padding(10) // ��ư �ֺ��� 10px ���� �߰�
		.VAlign(VAlign_Center) // ��ư�� ���� �߾� ����
		[
			SNew(SButton) // ��ư ����
			.Text(LOCTEXT("StartGame", "GameStart")) // ��ư�� �ؽ�Ʈ ǥ��
			.OnClicked(this, &SMainMenuWidget::OnStartGameClicked) 
		]


		// ���� ��ư
		+ SVerticalBox::Slot()
		.Padding(10)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(LOCTEXT("Settings", "Option"))
			.OnClicked(this, &SMainMenuWidget::OnSettingsClicked)
		]

		
		// ���� ���� ��ư
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
// END_SLATE_FUNCTION_BUILD_OPTIMIZATION // Slate UI ���� ����ȭ ����
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

