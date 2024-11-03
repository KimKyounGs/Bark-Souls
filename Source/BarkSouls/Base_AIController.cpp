// Fill out your copyright notice in the Description page of Project Settings.

#include "Base_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


ABase_AIController::ABase_AIController()
{


}

void ABase_AIController::BeginPlay()
{
    Super::BeginPlay();
    if(BehaviorTree != nullptr)
    {
        RunBehaviorTree(BehaviorTree);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsObject(TEXT("Player"),UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    }


}

void ABase_AIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}
