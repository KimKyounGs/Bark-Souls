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

    // �÷��̾ ������ Ȱ��ȭ�� ȭ��ҷ� �̵���Ű�� �Լ�
    void MovePlayerToLastBonfire();

    // ������ Ȱ��ȭ�� ȭ����� �����͸� ������
    FBonfireData GetLastActivatedBonfireData();

    // SaveGame ���� ����
    UPROPERTY()
    UBonfireSaveGame* SaveGameInstance;

    // ���̺� ���� �̸�
    UPROPERTY(EditAnywhere, Category = "Save System")
    FString SaveSlotName;
};



