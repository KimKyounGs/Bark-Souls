// Fill out your copyright notice in the Description page of Project Settings.
#include "AttackTokenComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BarkSoulsCharacter.h"
#include "Base_AIController.h"


//플레이어라면 AttackToken을 보유하게하고 Enemy가 공격시 플레이어의 AttackToken을 할당해주고 공격이 끝나면 반환한다 -> 그럼 플레이어가 처음 보유한 AttackToken의 수만큼의 Enemy만 한번에 공격가능 


// Sets default values for this component's properties
UAttackTokenComponent::UAttackTokenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackTokenComponent::BeginPlay()
{
	Super::BeginPlay();
	APawn* Pawn = Cast<APawn>(GetOwner());

	if(Pawn && Pawn->IsPlayerControlled())  //Player라면 AttackToken 할당
	{
		AttackTokenCount = StartAttackCount;
	}
	

	// ...
	
}


// Called every frame
void UAttackTokenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackTokenComponent::ReturnAttackToken()
{
	AttackReserveList[0]->RemoveAttackList();
	AttackReserveList.RemoveAt(0);
	AttackTokenCount += 1;

	if(AttackReserveList.Num() > 0)
	{ 
		AttackTokenCount -= 1;
		AttackReserveList[0]->ChangeStateAttack();
	}
}

bool UAttackTokenComponent::ReserveAttackToken(ABase_AIController* Target)
{
	AttackReserveList.Add(Target);
	if(AttackTokenCount > 0)
	{
		AttackTokenCount -= 1;
		Target->ChangeStateAttack();
	}
	return true;
	/*if(AttackTokenCount > 0)
	{
		AttackTokenCount -= 1;
		return true;
	}
	else
	{
		
		return false;
	}*/
}
