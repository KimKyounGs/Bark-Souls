// Fill out your copyright notice in the Description page of Project Settings.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

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
	
}

// Called every frame
void ADogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent != nullptr){
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputMove);
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputLook);
	}

}

void ADogCharacter::EnhancedInputMove(const FInputActionValue& Value){
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADogCharacter::EnhancedInputLook(const FInputActionValue& Value){
	FVector2D LookVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr){
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
	
}