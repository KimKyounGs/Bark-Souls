// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Base_AIController.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API ABase_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ABase_AIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, meta = (Allowprivateaccess = "true"))
	class UBehaviorTree* BehaviorTree; 


	
};
