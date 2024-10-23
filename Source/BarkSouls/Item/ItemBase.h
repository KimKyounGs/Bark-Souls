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
	FString itemID; // 아이템 ID
	UPROPERTY(EditAnywhere, Category = "Item")
	FString itemName; // 아이템 이름
	UPROPERTY(EditAnywhere, Category = "Item")
	FString itemDescription; // 아이템 설명
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* itemICon; // 아이템 아이콘(그림)
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 itemQuantity; // 아이템 수량
};
