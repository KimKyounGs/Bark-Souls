// Fill out your copyright notice in the Description page of Project Settings.
#include "BTT_KnightAttack.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GeneralEnemy.h"
#include "AIBehaviorComponent.h"

UBTT_KnightAttack::UBTT_KnightAttack()
{
    NodeName = "knight Attack";
}

EBTNodeResult::Type UBTT_KnightAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

        if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AActor* Owner = OwnerComp.GetAIOwner()-> GetPawn();
    if(Owner == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    FAIMoveRequest MoveReq;

    AActor* AttackTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

    MoveReq.SetGoalActor(AttackTarget);
    MoveReq.SetAcceptanceRadius(50.f);

    const FPathFollowingRequestResult MoveResult = (OwnerComp.GetAIOwner())->MoveTo(MoveReq);
    if(EPathFollowingRequestResult::AlreadyAtGoal == MoveResult.Code)
    {
        AGeneralEnemy* Enemy = Cast<AGeneralEnemy>(Owner);
        if(Enemy == nullptr)
        {
            return EBTNodeResult::Failed;
        }
        Enemy->Attack();
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasAttackToken"),false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RegisterAttackList"),false);
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), static_cast<uint8>(EAIStateType::AttackIdle));
    }

    return EBTNodeResult::Succeeded;
}
