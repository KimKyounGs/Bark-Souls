// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bonfire/BonfireTypes.h"
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

    // 플레이어를 마지막 활성화된 화톳불로 이동시키는 함수
    void MovePlayerToLastBonfire();

    // 마지막 활성화된 화톳불의 데이터를 가져옴
    FBonfireData GetLastActivatedBonfireData();

    // SaveGame 관련 변수
    UPROPERTY()
    UBonfireSaveGame* SaveGameInstance;

    // 세이브 슬롯 이름
    UPROPERTY(EditAnywhere, Category = "Save System")
    FString SaveSlotName;
};



