// Fill out your copyright notice in the Description page of Project Settings.


#include "BarkSoulsGameInstance.h"

void UBarkSoulsGameInstance::Init() 
{
	Super::Init();
	bShouldFadeIn = false;
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized - Bonfire Data Ready"));
}

void UBarkSoulsGameInstance::RegisterBonfire(FBonfireData NewBonfire)
{
	if (!BonfireMap.Contains(NewBonfire.BonfireID))
	{
		BonfireMap.Add(NewBonfire.BonfireID, NewBonfire);
		UE_LOG(LogTemp, Warning, TEXT("Registered Bonfire : %s"), *NewBonfire.BonfireName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Registered Bonfire : %s"), *NewBonfire.BonfireName.ToString());
	}
}

void UBarkSoulsGameInstance::SetSelectedBonfire(FName BonfireID)
{
	if (BonfireMap.Contains(BonfireID))
	{
		SelectedBonfire = BonfireID;
		UE_LOG(LogTemp, Warning, TEXT("Selected Bonfire: %s"), *BonfireID.ToString());
	}
}

FTransform UBarkSoulsGameInstance::GetBonfireTransform(FName BonfireID)
{
	FTransform OutTransform;
	OutTransform.SetLocation(FVector(FLT_MAX, FLT_MAX, FLT_MAX));
	if (BonfireMap.Contains(BonfireID))
	{
		OutTransform = BonfireMap[BonfireID].BonfireTransform;
	}

	return OutTransform;
}
