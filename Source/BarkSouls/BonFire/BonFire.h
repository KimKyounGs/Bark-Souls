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
	// 화톳불 위치 데이터
	static TMap<FName, FTransform> BonfireLocations;

	// 화톳불 등록 여부
	bool bIsRegistered;

	// 현재 화톳불 ID
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FName BonfireID;

	// 화톳불 메시
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BonfireMesh; 

	// 화톳불 콜리전 박스
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox; 

	UPROPERTY(EditAnywhere)
	class UMapResetComponent* MapResetComponent;

private:
	// 다른 화톳불로 순간이동
	UFUNCTION(BlueprintCallable, Category = "Bonfire")
	void TeleportPlayer(AActor* Player, FName TargetBonfireID);

	// 화톳불 위치 등록 -> 화톳불과 상호작용을 해야함 ID가 등록됨.
	void RegisterBonfireLocation();
public:
	// 화톳불 상화작용
	UFUNCTION()
	void Interact(AActor* Plyer);

};
