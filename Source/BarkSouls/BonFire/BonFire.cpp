// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "BonfireTeleportUI.h"
#include "Blueprint/UserWidget.h"
#include "BarkSouls/Character/DogCharacterController.h"

// 정적 변수 초기화
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

	// 컨트롤러 초기화.
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	// 월드 정보나 다른 액터에 의존한 위치 초기화
	if (!BonfireData.BonfireTransform.IsValid())
	{
		BonfireData.BonfireTransform = GetActorTransform(); // 현재 액터의 Transform으로 초기화
	}

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABonfire::OnOverlapEnd);
}

void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShowMessage(TEXT("Tick1"));
	// 플레이어가 범위 내에 있고 상호작용 키 입력이 있을 경우
	if (bPlayerInRange)
	{
		if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::E))
		{
			ShowMessage(TEXT("Tick3"));
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
		RegisterBonfireLocation();
		BonfireData.bIsActivated = true; // 등록 상태로 변경
		ShowMessage(TEXT("Bonfire activate"));
	}
	else
	{
		ShowMessage(TEXT("already Bonfire activated"));
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (ADogCharacterController* MyPC = Cast<ADogCharacterController>(PC))
		{
			if (AUIManager* UIManager = MyPC->GetUIManager())
			{
				UIManager->ShowUI(EUIType::BonfireUI);
			}
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