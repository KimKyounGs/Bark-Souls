// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GeneralEnemyAII.h"
#include "GeneralEnemy.generated.h"

class APatrolRoute;

UCLASS()
class BARKSOULS_API AGeneralEnemy : public AEnemyBase, public IGeneralEnemyAII
{
	GENERATED_BODY()

	UPROPERTY()
	int PatrolIndex = 0;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI",  meta = (AllowPrivateAccess = "true"))
    APatrolRoute* PatrolPath;
public:
	AGeneralEnemy();

	UFUNCTION(BlueprintCallable, Category = "AI")
	virtual APatrolRoute* GetPatrolRoute() const override;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override; 
};
