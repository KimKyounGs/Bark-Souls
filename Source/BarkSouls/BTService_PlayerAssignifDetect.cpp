// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerAssignifDetect.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIBehaviorComponent.h"
#include "AttackTokenComponent.h"
#include "Base_AIController.h"

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


    if(AIController->LineOfSightTo(Player) && Distance >= Player_Distance && Player_Distance >= 500) //Player가 보이고 Player와 AI 사이의 거리가 설정한 값 이하면 블랙보드 오브젝트값 할당
    { 
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(),static_cast<uint8>(EAIStateType::Chase)); //uint8을 원하므로 static_cast를 통해서 업캐스팅
        //OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),Player);
    }
    else if(Player_Distance <= 500 
    && OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("State")) != static_cast<uint8>(EAIStateType::AttackStart) &&
    !OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("RegisterAttackList")))
    {
        if(UAttackTokenComponent* AttackTokenComponent = Cast<UAttackTokenComponent>(Player->GetComponentByClass(UAttackTokenComponent::StaticClass())))
        {
            ABase_AIController* Base_Controller = Cast<ABase_AIController>(AIController);
            AttackTokenComponent->ReserveAttackToken(Base_Controller);
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RegisterAttackList"),true);
            /*bool HasAttackToken = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("HasAttackToken"));
            if(AttackTokenComponent->ReserveAttackToken()|| HasAttackToken)                                
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<uint8>(EAIStateType::AttackStart));
                OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasAttackToken"),true);
            }
            else
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(),static_cast<uint8>(EAIStateType::AttackIdle));
            }*/
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player가 AttackTokenComponent를 가지고 있지 않음"));
        }

        //OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());   
    }
    else if(Player_Distance <= 500 && 
    OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("RegisterAttackList")) && 
    OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("State")) != static_cast<uint8>(EAIStateType::AttackStart))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("State"),static_cast<uint8>(EAIStateType::AttackIdle));
    }
    else
    {
        if(Player_Distance >= 500)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(),static_cast<uint8>(EAIStateType::Idle));
        }
        
    }
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *);
}
