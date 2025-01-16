// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
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

	Player = Cast<ADogCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player)
	{
		ShowMessage(TEXT("Player not found"));
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
	ShowMessage("ABonfire::OnTeleport()");
}

void ABonfire::OnLeave()
{
	HideBonfireUI();
	ShowMessage("ABonfire::OnLeave()");
}

void ABonfire::TeleportPlayer(FName TargetBonfireID)
{
	if (!StaticActiveBonfires.Contains(TargetBonfireID))
	{
		ShowMessage("NO ID Bonfire");
		return;
	}

	const FBonfireData& TargetBonfire = StaticActiveBonfires[TargetBonfireID];
	
	// ���� �ʰ� �̵��� �� ��
	if (TargetBonfire.MapName != FName(*GetWorld()->GetMapName()))
	{
		// �ٸ� ������ �̵�
		UGameplayStatics::OpenLevel(this, TargetBonfire.MapName);

		// OpenLevel ��, ���� �ε�Ǹ� �÷��̾� ��ġ�� ����
	}
	else
	{
		// ���� �� �� �ڷ���Ʈ
		Player->SetActorTransform(TargetBonfire.BonfireTransform);
	}
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}