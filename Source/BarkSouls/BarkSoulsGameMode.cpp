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
        //SWeakWidget: Slate 위젯을 안전하게 추가하기 위한 래퍼 클래스
        //.PossiblyNullContent(MainMenuWidget.ToSharedRef()) :
        //    MainMenuWidget을 공유 포인터(TSharedRef<>)로 변환하여 UI에 추가
        //    UI가 없을 경우(null)에도 처리 가능하게 함
        GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuWidget.ToSharedRef()));

        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->bShowMouseCursor = true;
            PC->SetInputMode(FInputModeUIOnly());
        }
    }
}