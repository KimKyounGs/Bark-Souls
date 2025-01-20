// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireUI.h"
#include "Components/Button.h"

void UBonfireUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestButton)
	{
		RestButton->OnClicked.AddDynamic(this, &UBonfireUI::OnRestButtonClicked);
	}

	if (TeleportButton)
	{
		TeleportButton->OnClicked.AddDynamic(this, &UBonfireUI::OnTeleportButtonClicked);
	}

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &UBonfireUI::OnLeaveButtonClikced);
	}
}

void UBonfireUI::OnRestButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Rest button clicked!"));
}

void UBonfireUI::OnTeleportButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Teleport button clicked!"));
	if (UIManager)
	{
		// BonfireTeleportUI Ç¥½Ã
		UIManager->ShowUI(EUIType::BonfireTeleportUI);
	}
}

void UBonfireUI::OnLeaveButtonClikced()
{
	UE_LOG(LogTemp, Warning, TEXT("Leave button clicked!"));
	if (UIManager)
	{
		UIManager->HideUI();
	}
}
