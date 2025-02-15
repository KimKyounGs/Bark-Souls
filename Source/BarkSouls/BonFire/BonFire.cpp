// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "Blueprint/UserWidget.h"
#include "BarkSouls/Character/DogCharacterController.h"

// ���� ���� �ʱ�ȭ
TMap<FName, FBonfireData> ABonfire::StaticActiveBonfires;

ABonfire::ABonfire() : bPlayerInRange(false), bUsingBonfire(false)
{
	PrimaryActorTick.bCanEverTick = true;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));

	BonfireData.bIsActivated = false;
}

void ABonfire::BeginPlay()
{
	Super::BeginPlay();

	// ��Ʈ�ѷ� �ʱ�ȭ.
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	// ��ġ ����
	FTransform BonfireTransform = GetActorTransform(); 
	FVector NewLocation = BonfireTransform.GetLocation() + FVector(0, 0, 100);
	BonfireData.BonfireTransform.SetLocation(NewLocation);
	BonfireData.BonfireTransform = BonfireTransform;

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABonfire::OnOverlapEnd);
}

void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �÷��̾ ���� ���� �ְ� ��ȣ�ۿ� Ű �Է��� ���� ���
	if (bPlayerInRange)
	{
		if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::E))
		{
			Interact();  
		}
	}

}

void ABonfire::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor && OtherActor->IsA(ADogCharacter::StaticClass()))
	if (OtherActor)
	{
		bPlayerInRange = true;
		ShowMessage(TEXT("OnOverlapBegin"));
	}
}

void ABonfire::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bPlayerInRange = false;
		ShowMessage(TEXT("OnOverlapEnd"));
	}
}

void ABonfire::Interact()
{
	if (!BonfireData.bIsActivated) // ���� ��ϵ��� ���� ���
	{
		RegisterBonfireLocation();
		BonfireData.bIsActivated = true; // ��� ���·� ����
		ShowMessage(TEXT("Bonfire activate"));
	}
	else
	{
		ShowMessage(TEXT("already Bonfire activated"));
	}

	if (ADogCharacterController* ADogController = Cast<ADogCharacterController>(PlayerController))
	{
		if (AUIManager* UIManager = ADogController->GetUIManager())
		{
			UIManager->ShowUI(EUIType::BonfireUI);
		}
	}
}

void ABonfire::RegisterBonfireLocation()
{
	if (!BonfireData.BonfireID.IsNone())
	{
		StaticActiveBonfires.Add(BonfireData.BonfireID, BonfireData);
	}
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}