// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInventoryComponent::AddItem(AItemBase* Item)
{
    if (Item)
    {
        Items.Add(Item);
    }
}

void UInventoryComponent::RemoveItem(AItemBase* Item)
{
    if (Item)
    {
        Items.Remove(Item);
    }
}

bool UInventoryComponent::HasItem(AItemBase* Item) const
{
    return Items.Contains(Item);
}