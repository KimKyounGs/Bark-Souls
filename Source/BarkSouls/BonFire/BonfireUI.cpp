// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireUI.h"
#include "Components/Button.h"
#include "BonfireTeleportUI.h"

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
	bonfire->OnRest();
}

void UBonfireUI::OnTeleportButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Teleport button clicked!"));
	if (!TeleportUIClass) return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	// ���ο� Teleport UI ����
	UBonfireTeleportUI* TeleportUI = CreateWidget<UBonfireTeleportUI>(PlayerController, TeleportUIClass);
	if (TeleportUI)
	{
		TeleportUI->Initialize(bonfire); // OwningBonfire ����
		TeleportUI->AddToViewport();    // ȭ�鿡 �߰�
	}
	bonfire->OnTeleport();
}

void UBonfireUI::OnLeaveButtonClikced()
{
	UE_LOG(LogTemp, Warning, TEXT("Leave button clicked!"));
	bonfire->OnLeave();
}