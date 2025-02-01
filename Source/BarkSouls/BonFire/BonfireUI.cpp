// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	DogController = Cast<ADogCharacterController>(PlayerController);
}

void UBonfireUI::OnRestButtonClicked()
{

}

void UBonfireUI::OnTeleportButtonClicked()
{
	if (DogController)
	{
		AUIManager* UIManager = DogController->GetUIManager();
		if (UIManager)
		{
			UIManager->ShowUI(EUIType::BonfireTeleportUI);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No DogController"));
	}
}

void UBonfireUI::OnLeaveButtonClikced()
{
	UE_LOG(LogTemp, Warning, TEXT("Leave button clicked!"));
}
