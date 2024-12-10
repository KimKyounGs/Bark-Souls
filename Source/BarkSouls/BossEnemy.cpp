// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ABossEnemy::ABossEnemy()
{
    GetCharacterMovement()->GetNavMovementProperties()->bUseAccelerationForPaths = true;
    GetCharacterMovement()->MaxWalkSpeed = 400.f;

    GetCapsuleComponent()->SetCollisionProfileName("CapsuleEnemy");
    
    GetMesh()->SetCollisionProfileName("MeshEnemy");
}