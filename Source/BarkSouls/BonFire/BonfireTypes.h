#pragma once

#include "CoreMinimal.h" // 필수 헤더
#include "Components/Image.h"
#include "BonfireTypes.generated.h"

// 화톳불 관련 데이터 구조체 정의
USTRUCT(BlueprintType)
struct FBonfireData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireID; // 화톳불 ID

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireName; // 화톳불 이름

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FTransform BonfireTransform; // 화톳불 위치

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    bool bIsActivated; // 활성화 여부

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName LevelName; // 화톳불이 속한 레벨(Stage) 이름

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    UTexture2D* BonfireTexture; // 화톳불 이미지

};