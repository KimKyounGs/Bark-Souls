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

    // �⺻�� ����
    SaveSlotName = "SaveSlot"; // SaveGame�� ������ ���� �̸�
}

void ABarkSoulsGameMode::BeginPlay()
{
    Super::BeginPlay();

    // SaveGame �����͸� �ε��Ͽ� �÷��̾ ������ ȭ��� ��ġ�� �̵�
    MovePlayerToLastBonfire();
}

void ABarkSoulsGameMode::MovePlayerToLastBonfire()
{
    // SaveGame �ε�
    SaveGameInstance = Cast<UBonfireSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (!SaveGameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("No SaveGame Found!"));
        return;
    }

    // ������ Ȱ��ȭ�� ȭ��� ������ ��������
    FBonfireData LastBonfire = GetLastActivatedBonfireData();

    // �÷��̾� ��Ʈ�ѷ� �� �÷��̾� ��ġ ����
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

    // Ȱ��ȭ�� ȭ��� ��� Ȯ��
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