// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class BARKSOULS_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	FString itemID; // ������ ID
	UPROPERTY(EditAnywhere, Category = "Item")
	FString itemName; // ������ �̸�
	UPROPERTY(EditAnywhere, Category = "Item")
	FString itemDescription; // ������ ����
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* itemICon; // ������ ������(�׸�)
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 itemQuantity; // ������ ����
};
