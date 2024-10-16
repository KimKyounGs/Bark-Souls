// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerAssignifDetect.generated.h"

/**
 * 
 */
UCLASS()
class BARKSOULS_API UBTService_PlayerAssignifDetect : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerAssignifDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = Node)
	float Distance;	
};
