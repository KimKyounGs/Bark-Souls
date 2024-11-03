// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_KnightAttack.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBTT_KnightAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTT_KnightAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
