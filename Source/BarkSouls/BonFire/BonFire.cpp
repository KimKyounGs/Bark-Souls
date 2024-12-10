// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "Blueprint/UserWidget.h"

// ���� ���� �ʱ�ȭ
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
	if (!bIsRegistered) // ���� ��ϵ��� ���� ���
	{
		RegisterBonfireLocation();
		bIsRegistered = true; // ��� ���·� ����
		ShowMessage(TEXT("Bonfire activate"));
	}
	else
	{
		ShowMessage(TEXT("already Bonfire activated"));
	}

	if (!bUsingBonfire)
	{
		// �߰������� UI�� ���ų� ȿ���� ������ �� ����
		ShowBonfireUI();
	}
}

void ABonfire::ShowBonfireUI()
{
	if (BonfireWidget && PlayerController)
	{
		// 1. UI ���̰� ����
		BonfireWidget->SetVisibility(ESlateVisibility::Visible);
		bUsingBonfire = true;

		// 2. ���콺 Ŀ�� ���̰� �ϱ�
		PlayerController->bShowMouseCursor = true;

		// 3. �Է� ��� ����: UI ����
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		// 4. ���� �Ͻ� ����
		UGameplayStatics::SetGamePaused(this, true);

		ShowMessage("Good");
	}
}

void ABonfire::HideBonfireUI()
{
	if (BonfireWidget && PlayerController)
	{
		// 1. UI ����� 
		BonfireWidget->SetVisibility(ESlateVisibility::Hidden);
		bUsingBonfire = false;

		// 2. ���콺 Ŀ�� �����
		PlayerController->bShowMouseCursor = false;

		// 3. �Է� ��� ����: ���� ����
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		// 4. ���� �簳
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