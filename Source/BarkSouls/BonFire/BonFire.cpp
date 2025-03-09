// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonfire.h"
#include "Kismet/GameplayStatics.h"
#include "BonfireUI.h"
#include "Blueprint/UserWidget.h"
#include "BarkSouls/Character/DogCharacterController.h"
#include "BarkSouls/BarkSoulsGameInstance.h"
#include "NiagaraComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"

ABonfire::ABonfire() : bPlayerInRange(false), bUsingBonfire(false)
{
	PrimaryActorTick.bCanEverTick = true;

	BonfireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonfireMesh"));
	RootComponent = BonfireMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	MapResetComponent = CreateDefaultSubobject<UMapResetComponent>(TEXT("MapResetComponet"));

	BonfireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BonfireEffect"));
	BonfireEffect->SetupAttachment(RootComponent);

	BonfireLoopAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BonfireLoopAudio"));
	BonfireLoopAudioComponent->SetupAttachment(RootComponent);

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
			GameInstance->RegisterBonfire(BonfireData);
		}
		BonfireData.bIsActivated = true; // 등록 상태로 변경
		ShowMessage(TEXT("Bonfire activate"));
	}
	else
	{
		ShowMessage(TEXT("already Bonfire activated"));
	}

	// 나이아가라 (불) 활성화
	if (BonfireEffect)
	{
		BonfireEffect->Activate();
	}
	// 1. 불꽃 점화 사운드 (한 번만 재생)
	if (BonfireIgniteSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BonfireIgniteSound, GetActorLocation());
	}

	// 2. 지속되는 불꽃 사운드 (반복 + 어테뉴에이션)
	if (BonfireLoopSound && BonfireLoopAudioComponent)
	{
		BonfireLoopAudioComponent->SetSound(BonfireLoopSound);
		BonfireLoopAudioComponent->bIsUISound = false; 
		BonfireLoopAudioComponent->bAllowSpatialization = true; // 3D 위치 기반 사운드 활성화
		BonfireLoopAudioComponent->AttenuationSettings = BonfireSoundAttenuation; // 어테뉴에이션 적용
		BonfireLoopAudioComponent->Play();
	}

	FTimerHandle UITimerHandle;
	GetWorldTimerManager().SetTimer(UITimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			if (ADogCharacterController* ADogController = Cast<ADogCharacterController>(PlayerController))
			{
				if (AUIManager* UIManager = ADogController->GetUIManager())
				{
					UIManager->ShowUI(EUIType::BonfireUI);
				}
			}
		}), 2.0f, false);
}

void ABonfire::ShowMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Message);
}