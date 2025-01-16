// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BonfireSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBonfireSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY()
	FName LastActivatedBonfireID;

	UPROPERTY()
	FVector PlayerLocation;
};
