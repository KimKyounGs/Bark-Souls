// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireTypes.h"
#include "Components/Button.h"
#include "BonfireTeleportUI.generated.h"

UCLASS()
class BARKSOULS_API UBonfireTeleportUI : public UUserWidget
{
    GENERATED_BODY()

public:
    // ScrollBox에 추가된 버튼들
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* BonfireList;

    // 버튼과 ID를 매핑
    TMap<UButton*, FName> ButtonIDMap;

    // 화톳불 UI 초기화 함수
    UFUNCTION(BlueprintCallable)
    void InitializeTeleportUI(const TMap<FName, FBonfireData>& ActiveBonfires);

    // 버튼 클릭 이벤트 함수
    UFUNCTION()
    void OnBonfireClicked();

protected:
    virtual void NativeConstruct() override; // 초기화
};