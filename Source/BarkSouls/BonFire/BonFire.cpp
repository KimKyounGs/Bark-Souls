// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"

// 정적 변수 초기화
TMap<FName, FTransform> ABonfire::BonfireLocations;

ABonfire::ABonfire()
{
	PrimaryActorTick.bCanEverTick = true;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));

	bIsRegistered = false;
	bPlayerInRange = false;
}

void ABonfire::BeginPlay()
{
	Super::BeginPlay();
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABonfire::OnOverlapEnd);
}

void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 플레이어가 범위 내에 있고 상호작용 키 입력이 있을 경우
	if (bPlayerInRange)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::E))
		{
			Interact();
		}
	}
}

void ABonfire::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		bPlayerInRange = true;
		ShowMessage(TEXT("Press E to rest at the bonfire."));
	}
}

void ABonfire::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bPlayerInRange = false;
		ShowMessage(TEXT(""));
	}
}

void ABonfire::Interact()
{
	if (!bIsRegistered) // 아직 등록되지 않은 경우
	{
		RegisterBonfireLocation();
		bIsRegistered = true; // 등록 상태로 변경
		ShowMessage(TEXT("The bonfire is now lit!"));
	}
	else
	{
		ShowMessage(TEXT("The bonfire has been extinguished."));
	}

	// 추가적으로 UI를 열거나 효과를 실행할 수 있음
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
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