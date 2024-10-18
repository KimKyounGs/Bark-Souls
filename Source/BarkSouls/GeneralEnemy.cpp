// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AGeneralEnemy::AGeneralEnemy()
{
    GetCharacterMovement()->GetNavMovementProperties()->bUseAccelerationForPaths = true;
    GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

APatrolRoute *AGeneralEnemy::GetPatrolRoute() const
{
    if(PatrolPath != nullptr)
    {
        return PatrolPath;
    }
    return nullptr;
}

void AGeneralEnemy::BeginPlay()
{
    Super::BeginPlay();


}

void AGeneralEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}
