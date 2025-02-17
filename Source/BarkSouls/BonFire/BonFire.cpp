// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "Blueprint/UserWidget.h"
#include "BarkSouls/Character/DogCharacterController.h"
#include "BarkSouls/BarkSoulsGameInstance.h"

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

	// 컨트롤러 초기화.
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABonfire::OnOverlapEnd);
}

void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 플레이어가 범위 내에 있고 상호작용 키 입력이 있을 경우
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
	if (!BonfireData.bIsActivated) // 아직 등록되지 않은 경우
	{
		UBarkSoulsGameInstance* GameInstance = Cast<UBarkSoulsGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (GameInstance)
		{
			BonfireData.BonfireTransform = GetActorTransform();
			GameInstance->RegisterBonfire(BonfireData);
		}
		BonfireData.bIsActivated = true; // 등록 상태로 변경
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

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}