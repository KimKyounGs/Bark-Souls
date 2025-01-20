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
    // UIManager 참조
    UPROPERTY()
    UUIManager* UIManager;

    // 에디터에서 설정 가능한 UIManager 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUIManager> UIManagerClass;

public:
    // UIManager getter
    UUIManager* GetUIManager() const { return UIManager; }
};
