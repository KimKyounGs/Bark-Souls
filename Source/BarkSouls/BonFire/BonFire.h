// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "BarkSouls/DogCharacter.h"
#include "BonfireTypes.h"
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

	// 화톳불 데이터
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FBonfireData BonfireData;

	// 플레이어가 범위 내에 있는지 여부
	UPROPERTY(EditAnywhere, Category = "State")
	bool bPlayerInRange;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bUsingBonfire;

	// UI 위젯 클래스
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireUI> BonfireWidgetClass;

	// 생성된 UI 위젯 인스턴스
	UPROPERTY(EditAnywhere, Category = "UI")
	class UBonfireUI* BonfireWidget;

	// Teleport UI 클래스 타입
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireTeleportUI> TeleportUIClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	class UBonfireTeleportUI* TeleportUI;

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
	static TMap<FName, FBonfireData> StaticActiveBonfires;

	// 화톳불 상화작용                   
	UFUNCTION()
	void Interact();

	// UI 버튼과 연결된 함수들.
	UFUNCTION()
	void OnRest();

	UFUNCTION()
	void OnTeleport();

	UFUNCTION()
	void OnLeave();

	// 디버깅 용 함수
	void ShowMessage(FString Message);
};
