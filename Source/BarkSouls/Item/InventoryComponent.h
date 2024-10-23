// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BARKSOULS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    // 생성자
    UInventoryComponent();

    // 인벤토리에 들어있는 아이템 리스트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<AItemBase*> Items;

    // 아이템 추가 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(AItemBase* Item);

    // 아이템 제거 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(AItemBase* Item);

    // 인벤토리에서 아이템 검색 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(AItemBase* Item) const;
};
