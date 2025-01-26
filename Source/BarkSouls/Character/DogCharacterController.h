// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BarkSouls/BonFire/UIManager.h"
#include "DogCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API ADogCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:

public:
    UPROPERTY(EditAnywhere)
    AUIManager* UIManager;
    AUIManager* GetUIManager() const { return UIManager; }
};
