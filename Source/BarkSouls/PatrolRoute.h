// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class BARKSOULS_API APatrolRoute : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USplineComponent* Spline;
	
	UPROPERTY()
	int PatrolIndex = 0;

	UPROPERTY()
	int Direction = 1;

public:	
	// Sets default values for this actor's properties
	APatrolRoute();

	void IncrementPatrolRoute();

	FVector GetSplinePointPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
