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
	UStaticMeshComponent* BonfireMesh; // ȭ��� �޽�

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	// ��ɺ� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UMapResetComponent* MapResetComponent;
};
