// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonfireManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBonfireData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	FName BonfireID; // ȭ��� ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	FString BonfireName; // ȭ��� �̸�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	FString RegionName; // ���� �̸�
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	bool bActivated; // Ȱ��ȭ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	UTexture2D* PreviewImage; // �̸����� 
};

class BARKSOULS_API BonfireManager
{
public:
	// ȭ��� ������ �迭
	static TArray<FBonfireData> BonfireDataArray;

	// Ư�� ȭ����� Ȱ��ȭ �ϴ� �Լ�
	static void ActivateBonfire(FName BonfireID);
	
};
