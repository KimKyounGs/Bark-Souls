#pragma once

#include "CoreMinimal.h" // �ʼ� ���
#include "BonfireTypes.generated.h"

// ȭ��� ���� ������ ����ü ����
USTRUCT(BlueprintType)
struct FBonfireData
{
    GENERATED_BODY()

    // ȭ��� ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireID;

    // ȭ��� �̸�.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireName;

    // ȭ����� ��ġ�� �� �̸�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName MapName;

    // ȭ����� ��ġ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FTransform BonfireTransform;

    // ȭ��� Ȱ��ȭ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    bool bIsActivated;


};