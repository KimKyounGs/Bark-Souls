// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AttackTokenComponent.h"
#include "Kismet/GameplayStatics.h"


AGeneralEnemy::AGeneralEnemy()
{
    GetCharacterMovement()->GetNavMovementProperties()->bUseAccelerationForPaths = true;
    GetCharacterMovement()->MaxWalkSpeed = 400.f;
    AttackTokenComponent = CreateDefaultSubobject<UAttackTokenComponent>(TEXT("AttackTokenComponent"));
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
void AGeneralEnemy::OnAttackEnded()
{
    GetCharacterMovement()->MaxWalkSpeed = 100;
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    UAttackTokenComponent* PlayerAttackTokenComponent = Cast<UAttackTokenComponent>(Player->GetComponentByClass(UAttackTokenComponent::StaticClass()));
    PlayerAttackTokenComponent->ReturnAttackToken();
}

void AGeneralEnemy::Attack()
{
    float AttackDelay = PlayAnimMontage(AttackAnim);
    GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,&AGeneralEnemy::OnAttackEnded, AttackDelay,false);
    GetCharacterMovement()->MaxWalkSpeed = 0;    

}
