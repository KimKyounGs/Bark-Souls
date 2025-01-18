// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "BonfireTeleportUI.h"
#include "Blueprint/UserWidget.h"

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
	if (BonfireWidgetClass)
	{
		if (PlayerController)
		{
			BonfireWidget = CreateWidget<UBonfireUI>(PlayerController, BonfireWidgetClass);
			TeleportUI = CreateWidget<UBonfireTeleportUI>(PlayerController, TeleportUIClass);
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

	// Player변수 초기화
	Player = Cast<ADogCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player)
	{
		ShowMessage(TEXT("Player not found"));
	}
	
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

		ShowMessage("ShowBonfireUI");
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

		ShowMessage("HideBonfireUI");
	}
}

void ABonfire::RegisterBonfireLocation()
{
	if (!BonfireData.BonfireID.IsNone())
	{
		StaticActiveBonfires.Add(BonfireData.BonfireID, BonfireData);
	}
}

void ABonfire::OnRest()
{
	ShowMessage("ABonfire::OnRest()");
}

void ABonfire::OnTeleport()
{
	if (!PlayerController)
	{
		ShowMessage("PlayerController not found!");
		return;
	}

	// BonfireTeleportUI 클래스를 확인
	if (!TeleportUIClass)
	{
		ShowMessage("TeleportUIClass is not set!");
		return;
	}

	// BonfireTeleportUI 생성
	if (TeleportUIClass)
	{
		// 활성화된 화톳불 데이터를 전달
		TeleportUI->InitializeUI(StaticActiveBonfires);

		// UI를 화면에 추가
		TeleportUI->AddToViewport();

		// 입력 모드 전환: UI 전용
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		// 마우스 커서를 보이게 설정
		PlayerController->bShowMouseCursor = true;

		// 게임 일시 정지
		UGameplayStatics::SetGamePaused(this, true);

		ShowMessage("Teleport UI opened.");
	}
	else
	{
		ShowMessage("Failed to create Teleport UI!");
	}
}

void ABonfire::OnLeave()
{
	HideBonfireUI();
	ShowMessage("ABonfire::OnLeave()");
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}