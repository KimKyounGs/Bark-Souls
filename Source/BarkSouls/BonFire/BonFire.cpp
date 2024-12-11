// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "Blueprint/UserWidget.h"

// 정적 변수 초기화
TMap<FName, FTransform> ABonfire::BonfireLocations;

ABonfire::ABonfire() : bIsRegistered(false), bPlayerInRange(false), bUsingBonfire(false)
{
	PrimaryActorTick.bCanEverTick = true;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));

}

void ABonfire::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (BonfireWidgetClass)
	{
		if (PlayerController)
		{
			BonfireWidget = CreateWidget<UBonfireUI>(PlayerController, BonfireWidgetClass);
			if (BonfireWidget)
			{
				BonfireWidget->AddToViewport();
				BonfireWidget->SetVisibility(ESlateVisibility::Hidden);

			}
		}
		else
		{
			ShowMessage(TEXT("NO Controller"));
		}
	}
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
	if (OtherActor && OtherActor != this)
	{
		bPlayerInRange = true;
		ShowMessage(TEXT("Press E"));
	}
}

void ABonfire::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bPlayerInRange = false;
		ShowMessage(TEXT(""));
		HideBonfireUI();
	}
}

void ABonfire::Interact()
{
	if (!bIsRegistered) // 아직 등록되지 않은 경우
	{
		RegisterBonfireLocation();
		bIsRegistered = true; // 등록 상태로 변경
		ShowMessage(TEXT("Bonfire activate"));
	}
	else
	{
		ShowMessage(TEXT("already Bonfire activated"));
	}

	if (!bUsingBonfire)
	{
		// 추가적으로 UI를 열거나 효과를 실행할 수 있음
		ShowBonfireUI();
	}
}

void ABonfire::ShowBonfireUI()
{
	if (BonfireWidget && PlayerController)
	{
		// 1. UI 보이게 설정
		BonfireWidget->SetVisibility(ESlateVisibility::Visible);
		bUsingBonfire = true;

		// 2. 마우스 커서 보이게 하기
		PlayerController->bShowMouseCursor = true;

		// 3. 입력 모드 설정: UI 전용
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		// 4. 게임 일시 정지
		UGameplayStatics::SetGamePaused(this, true);

		ShowMessage("Good");
	}
}

void ABonfire::HideBonfireUI()
{
	if (BonfireWidget && PlayerController)
	{
		// 1. UI 숨기기 
		BonfireWidget->SetVisibility(ESlateVisibility::Hidden);
		bUsingBonfire = false;

		// 2. 마우스 커서 숨기기
		PlayerController->bShowMouseCursor = false;

		// 3. 입력 모드 설정: 게임 전용
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		// 4. 게임 재개
		UGameplayStatics::SetGamePaused(this, false);

		ShowMessage("Bad");
	}
}

void ABonfire::RegisterBonfireLocation()
{
	if (!BonfireID.IsNone())
	{
		BonfireLocations.Add(BonfireID, GetActorTransform());
	}
}

void ABonfire::OnRest()
{
	ShowMessage("ABonfire::OnRest()");
}

void ABonfire::OnTeleport()
{
	ShowMessage("ABonfire::OnTeleport()");
}

void ABonfire::OnLeave()
{
	HideBonfireUI();
	ShowMessage("ABonfire::OnLeave()");
}

void ABonfire::TeleportPlayer(FName TargetBonfireID)
{
	if (!BonfireLocations.Contains(TargetBonfireID))
	{
		ShowMessage("NO ID Bonfire");
		return;
	}

	FTransform TargetTransform = BonfireLocations[TargetBonfireID];
	Player->TeleportPlayer(TargetTransform);
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}