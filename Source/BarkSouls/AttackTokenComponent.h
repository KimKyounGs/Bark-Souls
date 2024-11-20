// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackTokenComponent.generated.h"


class ABase_AIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BARKSOULS_API UAttackTokenComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	int AttackTokenCount;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int StartAttackCount = 1;

	UPROPERTY()
	TArray<ABase_AIController*> AttackReserveList;
public:	
	// Sets default values for this component's properties
	UAttackTokenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ReturnAttackToken();

	UFUNCTION()
	bool ReserveAttackToken(ABase_AIController* Target);
		
};
