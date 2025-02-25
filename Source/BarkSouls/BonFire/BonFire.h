// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
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

	// 나이아가라 이팩트
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraComponent* BonfireEffect; // 불꽃 이펙트

	// 사운드 변수 추가
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* BonfireIgniteSound; // 불꽃 점화 사운드 (한 번만 재생)

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* BonfireLoopSound;   // 지속되는 화톳불 사운드 (반복 재생)

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundAttenuation* BonfireSoundAttenuation; // 어테뉴에이션 설정

	UPROPERTY()
	class UAudioComponent* BonfireLoopAudioComponent; //반복 재생을 위한 오디오 컴포넌트

	APlayerController* PlayerController;

private:


public:

	// 화톳불 상화작용                   
	UFUNCTION()
	void Interact();

	// 디버깅 용 함수
	void ShowMessage(FString Message);
};
