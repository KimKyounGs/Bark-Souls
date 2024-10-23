// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	itemID = "Default Item ID";
	itemName = "Default Item Name";
	itemDescription = "Default Item Description";
	itemICon = nullptr;
	itemQuantity = 0;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}


