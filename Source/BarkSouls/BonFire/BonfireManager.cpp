// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireManager.h"

TArray<FBonfireData> BonfireManager::BonfireDataArray = {
    { "Stage1-1", "차가운 골짜기의 볼트", "로스릭의 높은 벽", false, nullptr },
    { "Stage1-2", "높은 벽의 탑", "로스릭의 높은 벽", true, nullptr }
};

// 화톳불을 활성화 상태로 설정
void BonfireManager::ActivateBonfire(FName BonfireID)
{
    for (auto& Bonfire : BonfireDataArray)  // 모든 화톳불을 순회
    {
        if (Bonfire.BonfireID == BonfireID)  // ID가 일치하면
        {
            Bonfire.bActivated = true;  // 활성화
            break;
        }
    }
}