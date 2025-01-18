#pragma once

#include "CoreMinimal.h" // �ʼ� ���
#include "BonfireTypes.generated.h"

// ȭ��� ���� ������ ����ü ����
USTRUCT(BlueprintType)
struct FBonfireData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FTransform BonfireTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    bool bIsActivated; // Ȱ��ȭ ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName MapName; // ȭ����� ���� ����(Stage) �̸�


};