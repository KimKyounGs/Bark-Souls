// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerAssignifDetect.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerAssignifDetect::UBTService_PlayerAssignifDetect()
{
    NodeName = "Player Assign if Detected";
}

void UBTService_PlayerAssignifDetect::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(Player == nullptr || AIController == nullptr) 
    {
        return;
    }

    AActor* Owner = AIController->GetPawn();
    
    float Player_Distance = UKismetMathLibrary::Vector_Distance(Player->GetActorLocation(),Owner->GetActorLocation());


    if(AIController->LineOfSightTo(Player) && Distance >= Player_Distance) //Player가 보이고 Player와 AI 사이의 거리가 설정한 값 이하면 블랙보드 오브젝트값 할당
    { 
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),Player);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }

}
