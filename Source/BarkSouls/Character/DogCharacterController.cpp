// Fill out your copyright notice in the Description page of Project Settings.


#include "DogCharacterController.h"

void ADogCharacterController::BeginPlay()
{
    Super::BeginPlay();

    // UIManager 생성
    if (UIManagerClass)
    {
        UIManager = NewObject<UUIManager>(this, UIManagerClass);
        if (UIManager)
        {
            UIManager->Initialize(this); // 초기화
            UE_LOG(LogTemp, Log, TEXT("UIManager initialized successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create UIManager!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("UIManagerClass is not set in PlayerController!"));
    }
}