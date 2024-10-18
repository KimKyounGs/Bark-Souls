// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GeneralEnemyAII.generated.h"


class APatrolRoute;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGeneralEnemyAII : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BARKSOULS_API IGeneralEnemyAII
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual APatrolRoute* GetPatrolRoute() const = 0;

};
