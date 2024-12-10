// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "BarkSouls/DogCharacter.h"
#include "Bonfire.generated.h"

UCLASS()
class BARKSOULS_API ABonfire : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ABonfire();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
private:
	// 화톳불 메시
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* BonfireMesh;

	// 화톳불 콜리전 박스
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* InteractionBox;

	// 맵 리셋 컴포넌트
	UPROPERTY(EditAnywhere, Category = "Component")
	class UMapResetComponent* MapResetComponent;

	// 화톳불 등록 여부
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	bool bIsRegistered;

	// 현재 화톳불 ID
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FName BonfireID;

	// 플레이어가 범위 내에 있는지 여부
	UPROPERTY(EditAnywhere, Category = "State")
	bool bPlayerInRange;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bUsingBonfire;

	// UI 위젯 클래스
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireUI> BonfireWidgetClass;

	// 생성된 UI 위젯 인스턴스
	UPROPERTY()
	class UBonfireUI* BonfireWidget;

	ADogCharacter* Player;
	// 나중에 고치기
	APlayerController* PlayerController;

private:
	// 화톳불 위치 등록 -> 화톳불과 상호작용을 해야 ID가 등록됨.
	void RegisterBonfireLocation();
	// UI
	void ShowBonfireUI();
	void HideBonfireUI();

public:
	// 화톳불 위치 데이터
	static TMap<FName, FTransform> BonfireLocations;

	// 화톳불 상화작용                   
	UFUNCTION()
	void Interact();

	// 다른 화톳불로 순간이동
	UFUNCTION(BlueprintCallable, Category = "Bonfire")
	void TeleportPlayer(FName TargetBonfireID);

	// UI 버튼
	UFUNCTION()
	void OnRest();

	UFUNCTION()
	void OnTeleport();

	UFUNCTION()
	void OnLeave();

	// 디버깅 용 함수
	void ShowMessage(FString Message);
};
