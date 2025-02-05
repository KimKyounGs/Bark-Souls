#pragma once

#include "CoreMinimal.h" // �ʼ� ���
#include "Components/Image.h"
#include "BonfireTypes.generated.h"

// ȭ��� ���� ������ ����ü ����
USTRUCT(BlueprintType)
struct FBonfireData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireID; // ȭ��� ID

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireName; // ȭ��� �̸�

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FTransform BonfireTransform; // ȭ��� ��ġ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    bool bIsActivated; // Ȱ��ȭ ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName LevelName; // ȭ����� ���� ����(Stage) �̸�

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    UTexture2D* BonfireTexture; // ȭ��� �̹���

};