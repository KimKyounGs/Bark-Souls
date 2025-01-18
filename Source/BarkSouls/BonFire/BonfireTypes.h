#pragma once

#include "CoreMinimal.h" // 필수 헤더
#include "BonfireTypes.generated.h"

// 화톳불 관련 데이터 구조체 정의
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
    bool bIsActivated; // 활성화 여부

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonfire")
    FName MapName; // 화톳불이 속한 레벨(Stage) 이름


};