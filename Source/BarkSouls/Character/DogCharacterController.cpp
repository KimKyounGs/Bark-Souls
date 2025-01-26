// Fill out your copyright notice in the Description page of Project Settings.


#include "DogCharacterController.h"
#include "Kismet/GameplayStatics.h"

void ADogCharacterController::BeginPlay()
{
    Super::BeginPlay();

    if (UIManager)
    {
        UE_LOG(LogTemp, Log, TEXT("UIManager successfully found and set."));
    }

    // UIManager 가져오기
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUIManager::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        UIManager = Cast<AUIManager>(FoundActors[0]);
        if (UIManager)
        {
            UE_LOG(LogTemp, Log, TEXT("UIManager successfully found and set."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No UIManager found in the level!"));
    }
}