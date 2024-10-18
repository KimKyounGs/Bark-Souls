// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveAlongPatrolRoute.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include  "GeneralEnemyAII.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_MoveAlongPatrolRoute::UBTT_MoveAlongPatrolRoute()
{
    NodeName = "Move PatrolRoute";
}

EBTNodeResult::Type UBTT_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
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

    APatrolRoute* PatrolRoute;

    if (IGeneralEnemyAII* EnemyAII = Cast<IGeneralEnemyAII>(Owner))
    {
        PatrolRoute = EnemyAII->GetPatrolRoute();
        if(PatrolRoute == nullptr)
        {
            return EBTNodeResult::Failed;
        }


        FAIMoveRequest MoveReq;
        MoveReq.SetGoalLocation(PatrolRoute->GetSplinePointPosition());
        MoveReq.SetAcceptanceRadius(10.f);

        const FPathFollowingRequestResult MoveResult = (OwnerComp.GetAIOwner())->MoveTo(MoveReq);
        if(EPathFollowingRequestResult::AlreadyAtGoal == MoveResult.Code)
        {
            PatrolRoute->IncrementPatrolRoute();
        }


        //(OwnerComp.GetAIOwner())->MoveToLocation(PatrolRoute->GetSplinePointPosition());

        //OwnerComp.GetAIOwner()->ReceiveMoveCompleted.AddDynamic(this,);
        //PatrolRoute->IncrementPatrolRoute();
    }
    else
    {
        return EBTNodeResult::Failed;
    }



    return EBTNodeResult::Succeeded;
}
