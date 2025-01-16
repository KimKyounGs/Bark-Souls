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

    // 기본값 설정
    SaveSlotName = "SaveSlot"; // SaveGame을 저장할 슬롯 이름
}

void ABarkSoulsGameMode::BeginPlay()
{
    Super::BeginPlay();

    // SaveGame 데이터를 로드하여 플레이어를 마지막 화톳불 위치로 이동
    MovePlayerToLastBonfire();
}

void ABarkSoulsGameMode::MovePlayerToLastBonfire()
{
    // SaveGame 로드
    SaveGameInstance = Cast<UBonfireSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (!SaveGameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("No SaveGame Found!"));
        return;
    }

    // 마지막 활성화된 화톳불 데이터 가져오기
    FBonfireData LastBonfire = GetLastActivatedBonfireData();

    // 플레이어 컨트롤러 및 플레이어 위치 설정
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController && PlayerController->GetPawn())
    {
        PlayerController->GetPawn()->SetActorTransform(LastBonfire.BonfireTransform);
        UE_LOG(LogTemp, Log, TEXT("Player moved to last bonfire: %s"), *LastBonfire.BonfireName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController or Pawn not found!"));
    }
}

FBonfireData ABarkSoulsGameMode::GetLastActivatedBonfireData()
{
    FBonfireData BonfireData;

    // 활성화된 화톳불 목록 확인
    if (ABonfire::StaticActiveBonfires.Contains(SaveGameInstance->LastActivatedBonfireID))
    {
        BonfireData = ABonfire::StaticActiveBonfires[SaveGameInstance->LastActivatedBonfireID];
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Last activated bonfire ID not found in active bonfires!"));
    }

    return BonfireData;
}