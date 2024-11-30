// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "Bonfire.generated.h"

UCLASS()
class BARKSOULS_API ABonfire : public AActor
{
	GENERATED_BODY()

public:
	ABonfire();

protected:
	virtual void BeginPlay() override;

public:
	// virtual void Tick(float DeltaTime) override;

private:
	// ȭ��� ��ġ ������
	static TMap<FName, FTransform> BonfireLocations;

	// ȭ��� ��� ����
	bool bIsRegistered;

	// ���� ȭ��� ID
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FName BonfireID;

	// ȭ��� �޽�
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BonfireMesh; 

	// ȭ��� �ݸ��� �ڽ�
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox; 

	UPROPERTY(EditAnywhere)
	class UMapResetComponent* MapResetComponent;

private:
	// �ٸ� ȭ��ҷ� �����̵�
	UFUNCTION(BlueprintCallable, Category = "Bonfire")
	void TeleportPlayer(AActor* Player, FName TargetBonfireID);

	// ȭ��� ��ġ ��� -> ȭ��Ұ� ��ȣ�ۿ��� �ؾ��� ID�� ��ϵ�.
	void RegisterBonfireLocation();
public:
	// ȭ��� ��ȭ�ۿ�
	UFUNCTION()
	void Interact(AActor* Plyer);

};
