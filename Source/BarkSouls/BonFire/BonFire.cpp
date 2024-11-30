// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonfire.h"

// ���� ���� �ʱ�ȭ
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
	if (!bIsRegistered) // ���� ��ϵ��� ���� ���
	{
		RegisterBonfireLocation();
		bIsRegistered = true; // ��� ���·� ����
		UE_LOG(LogTemp, Log, TEXT("ȭ��� ��� �Ϸ�: %s"), *BonfireID.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("�̹� ��ϵ� ȭ���: %s"), *BonfireID.ToString());
	}

	// �߰������� UI�� ���ų� ȿ���� ������ �� ����
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
		UE_LOG(LogTemp, Warning, TEXT("ȭ���ID �������� ����!"));
		return;
	}

	FTransform TargetTransform = BonfireLocations[TargetBonfireID];
	Player->SetActorLocation(TargetTransform.GetLocation());
	Player->SetActorRotation(TargetTransform.GetRotation().Rotator());

	// ȿ�� ������ ������.

}