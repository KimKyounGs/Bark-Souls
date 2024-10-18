// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveAlongPatrolRoute.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBTT_MoveAlongPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTT_MoveAlongPatrolRoute();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
