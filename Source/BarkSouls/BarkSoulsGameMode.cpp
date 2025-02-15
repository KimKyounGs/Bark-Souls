// Copyright Epic Games, Inc. All Rights Reserved.

#include "BarkSoulsGameMode.h"
#include "BarkSoulsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BonFire/BonfireSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BonFire/Bonfire.h"

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

}