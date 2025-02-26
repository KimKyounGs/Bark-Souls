// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bonfire/BonfireTypes.h"
#include "BarkSouls/UI/SMainMenuWidget.h"
#include "BarkSoulsGameMode.generated.h"

// Forward Declaration
class UBonfireSaveGame;

UCLASS(minimalapi)
class ABarkSoulsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABarkSoulsGameMode();
protected:
    virtual void BeginPlay() override;

private:
	class TSharedPtr<SMainMenuWidget> MainMenuWidget;
};



