// Fill out your copyright notice in the Description page of Project Settings.


#include "BonFire.h"

ABonFire::ABonFire()
{
	PrimaryActorTick.bCanEverTick = true;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));
}

void ABonFire::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABonFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABonFire::Interact(AActor* Plyer)
{
	// 
}
