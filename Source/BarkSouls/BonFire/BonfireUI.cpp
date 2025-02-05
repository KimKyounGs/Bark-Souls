// Fill out your copyright notice in the Description page of Project Settings.

#include "BonfireUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UIManager.h"

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

	UIManager = Cast<AUIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AUIManager::StaticClass()));

}

void UBonfireUI::OnRestButtonClicked()
{

}

void UBonfireUI::OnTeleportButtonClicked()
{
	if (UIManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnTeleportButtonClicked"));
		UIManager->ShowUI(EUIType::BonfireTeleportUI);
	}
}

void UBonfireUI::OnLeaveButtonClikced()
{
	if (UIManager)
	{
		UIManager->HideUI();
	}
}