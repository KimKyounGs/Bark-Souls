// Copyright Epic Games, Inc. All Rights Reserved.

#include "BarkSoulsGameMode.h"
#include "BarkSoulsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "SlateBasics.h"
#include "SlateExtras.h" 


ABarkSoulsGameMode::ABarkSoulsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABarkSoulsGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine && GEngine->GameViewport)
    {
        MainMenuWidget = SNew(SMainMenuWidget);
        //SWeakWidget: Slate ������ �����ϰ� �߰��ϱ� ���� ���� Ŭ����
        //.PossiblyNullContent(MainMenuWidget.ToSharedRef()) :
        //    MainMenuWidget�� ���� ������(TSharedRef<>)�� ��ȯ�Ͽ� UI�� �߰�
        //    UI�� ���� ���(null)���� ó�� �����ϰ� ��
        GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuWidget.ToSharedRef()));

        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->bShowMouseCursor = true;
            PC->SetInputMode(FInputModeUIOnly());
        }
    }
}