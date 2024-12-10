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
	FName BonfireID; // 화톳불 ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	FString BonfireName; // 화톳불 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	FString RegionName; // 지역 이름
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	bool bActivated; // 활성화 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BonfireData")
	UTexture2D* PreviewImage; // 미리보기 
};

class BARKSOULS_API BonfireManager
{
public:
	// 화톳불 데이터 배열
	static TArray<FBonfireData> BonfireDataArray;

	// 특정 화톳불을 활성화 하는 함수
	static void ActivateBonfire(FName BonfireID);
	
};
