// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class DamageTypes : uint8
{
	heavyDamage UMETA(DisplayName = "heavyDamage"), 
	LightDamage UMETA(DisplayName = "LightDamage")
};




class BARKSOULS_API DB
{
public:
	DB();
	~DB();


};
