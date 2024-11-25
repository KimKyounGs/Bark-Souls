// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BonFire.generated.h"

UCLASS()
class BARKSOULS_API ABonFire : public AActor
{
	GENERATED_BODY()
	
public:	
	ABonFire();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Interact(AActor* Plyer);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BonfireMesh; // 화톳불 메시

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	// 기능별 컴포넌트
	UPROPERTY(EditAnywhere)
	class UMapResetComponent* MapResetComponent;
};
