// Fill out your copyright notice in the Description page of Project Settings.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>

#include "DogCharacter.h"

// Sets default values
ADogCharacter::ADogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>InputMappingContext(TEXT("/Game/Kwanik/Input/IMC_Player.IMC_Player"));
	if(InputMappingContext.Succeeded()){
		DefaultMappingContext = InputMappingContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionMove(TEXT("/Game/Kwanik/Input/IA_Move.IA_Move"));
	if(InputActionMove.Succeeded()){
		InputToMove = InputActionMove.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionLook(TEXT("/Game/Kwanik/Input/IA_Look.IA_Look"));
	if(InputActionLook.Succeeded()){
		InputToLook = InputActionLook.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionRun(TEXT("/Game/Kwanik/Input/IA_RunAndRoll.IA_RunAndRoll"));
	if(InputActionRun.Succeeded()){
		InputToRun = InputActionRun.Object;
	}

	//springArm
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
		// 차후 값 수정
	springArmComp->SetRelativeLocation(FVector(0, 30, 0)); 
	springArmComp->TargetArmLength = 200;

	//Camera
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);

}

// Called when the game starts or when spawned
void ADogCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController != nullptr){
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()
		);
		if(Subsystem != nullptr){
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	InputToRun->Triggers.Add(RollTrigger);
	InputToRun->Triggers.Add(RunTrigger);
	
}

// Called every frame
void ADogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input(Override)
void ADogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent != nullptr){
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputMove);
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputLook);
		EnhancedInputComponent->BindAction(InputToRun, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputRun);
	}

}

void ADogCharacter::EnhancedInputMove(const FInputActionValue& Value){
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	//트리거 출력 결과 -> Tab : 0, 0	Hold : +1, 0
	//WASD 입력중에 spacebar를 입력하는 경우 -> 현재 입력되고 있는 Vector의 x값이 무조건 1로 변함

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y*0.5);
		AddMovementInput(RightDirection, MovementVector.X*0.5);
	}
}

void ADogCharacter::EnhancedInputLook(const FInputActionValue& Value){
	FVector2D LookVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr){
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
	
}
void ADogCharacter::EnhancedInputRun(const FInputActionValue& Value){
	bool bIsTriggered = Value.Get<bool>();
	UE_LOG(LogTemp, Display, TEXT("Value = %s"), bIsTriggered ? TEXT("true") : TEXT("false")); //trigger 출력
	//bool 변수 변화를 주고
	//EnhancedInputMove에 넘겨주기
	//FVector CurrentVelocity = GetVelocity();
	//UE_LOG(LogTemp, Display, TEXT("Current = %s"), *CurrentVelocity.ToString()); 
	
	//FRotator ControlRotation = Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator; 
	//FRotator YawRotation(0, ControlRotation.Yaw, 0);
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//FVector LaunchVelocity = ForwardDirection * 5;
	//AddMovementInput(LaunchVelocity.GetSafeNormal(), 1000.0f);
	//UE_LOG(LogTemp, Display, TEXT("Launch = %s"), *LaunchVelocity.ToString()); 
	
	//그리고 길게 눌렸을때는
	//Roll 애니메이션 재생해야지 뭐
}