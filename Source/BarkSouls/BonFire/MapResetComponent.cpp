// Fill out your copyright notice in the Description page of Project Settings.


#include "MapResetComponent.h"

UMapResetComponent::UMapResetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UMapResetComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UMapResetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

