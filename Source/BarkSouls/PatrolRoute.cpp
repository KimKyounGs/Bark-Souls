// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"
#include "Components/SplineComponent.h"


// Sets default values
APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatrolRoute::IncrementPatrolRoute()
{
	PatrolIndex += Direction;
	if(PatrolIndex == 0)
	{
		Direction = 1;
	}
	else if(PatrolIndex == (Spline->GetNumberOfSplinePoints())-1)
	{
		Direction = -1;
	}
}

FVector APatrolRoute::GetSplinePointPosition()
{
    return Spline->GetLocationAtSplinePoint(PatrolIndex,ESplineCoordinateSpace::World);
}
