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
    // ������
    UInventoryComponent();

    // �κ��丮�� ����ִ� ������ ����Ʈ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<AItemBase*> Items;

    // ������ �߰� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(AItemBase* Item);

    // ������ ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(AItemBase* Item);

    // �κ��丮���� ������ �˻� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(AItemBase* Item) const;
};
