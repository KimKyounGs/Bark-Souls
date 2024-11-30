// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonfire.h"

// 정적 변수 초기화
TMap<FName, FTransform> ABonfire::BonfireLocations;

ABonfire::ABonfire()
{
	PrimaryActorTick.bCanEverTick = false;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));

	bIsRegistered = false;
}

void ABonfire::BeginPlay()
{
	Super::BeginPlay();

}

void ABonfire::Interact(AActor* Player)
{
	if (!bIsRegistered) // 아직 등록되지 않은 경우
	{
		RegisterBonfireLocation();
		bIsRegistered = true; // 등록 상태로 변경
		UE_LOG(LogTemp, Log, TEXT("화톳불 등록 완료: %s"), *BonfireID.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("이미 등록된 화톳불: %s"), *BonfireID.ToString());
	}

	// 추가적으로 UI를 열거나 효과를 실행할 수 있음
}

void ABonfire::RegisterBonfireLocation()
{
	if (!BonfireID.IsNone())
	{
		BonfireLocations.Add(BonfireID, GetActorTransform());
	}
}

void ABonfire::TeleportPlayer(AActor* Player, FName TargetBonfireID)
{
	if (!BonfireLocations.Contains(TargetBonfireID))
	{
		UE_LOG(LogTemp, Warning, TEXT("화톳불ID 존재하지 않음!"));
		return;
	}

	FTransform TargetTransform = BonfireLocations[TargetBonfireID];
	Player->SetActorLocation(TargetTransform.GetLocation());
	Player->SetActorRotation(TargetTransform.GetRotation().Rotator());

	// 효과 넣으면 좋을듯.

}