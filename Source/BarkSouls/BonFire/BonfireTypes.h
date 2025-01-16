#pragma once

#include "CoreMinimal.h" // 필수 헤더
#include "BonfireTypes.generated.h"

// 화톳불 관련 데이터 구조체 정의
USTRUCT(BlueprintType)
struct FBonfireData
{
    GENERATED_BODY()

    // 화톳불 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireID;

    // 화톳불 이름.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName BonfireName;

    // 화톳불이 위치한 맵 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName MapName;

    // 화톳불의 위치 정보
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FTransform BonfireTransform;

    // 화톳불 활성화 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    bool bIsActivated;


};