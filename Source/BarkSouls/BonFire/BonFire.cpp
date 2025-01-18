// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "BonfireTeleportUI.h"
#include "Blueprint/UserWidget.h"

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

	// Player���� �ʱ�ȭ
	Player = Cast<ADogCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player)
	{
		ShowMessage(TEXT("Player not found"));
	}
	
	// ���� ������ �ٸ� ���Ϳ� ������ ��ġ �ʱ�ȭ
	if (!BonfireData.BonfireTransform.IsValid())
	{
		BonfireData.BonfireTransform = GetActorTransform(); // ���� ������ Transform���� �ʱ�ȭ
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

		ShowMessage("ShowBonfireUI");
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

	// BonfireTeleportUI Ŭ������ Ȯ��
	if (!TeleportUIClass)
	{
		ShowMessage("TeleportUIClass is not set!");
		return;
	}

	// BonfireTeleportUI ����
	if (TeleportUIClass)
	{
		// Ȱ��ȭ�� ȭ��� �����͸� ����
		TeleportUI->InitializeUI(StaticActiveBonfires);

		// UI�� ȭ�鿡 �߰�
		TeleportUI->AddToViewport();

		// �Է� ��� ��ȯ: UI ����
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		// ���콺 Ŀ���� ���̰� ����
		PlayerController->bShowMouseCursor = true;

		// ���� �Ͻ� ����
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