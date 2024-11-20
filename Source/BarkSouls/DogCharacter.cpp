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
	bAttacking = false;
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
	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionRoll(TEXT("/Game/Kwanik/Input/IA_RunAndRoll.IA_RunAndRoll"));
	if(InputActionRoll.Succeeded()){
		InputToRoll = InputActionRoll.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionFight(TEXT("/Game/Kwanik/Input/IA_Fight.IA_Fight"));
	if(InputActionFight.Succeeded()){
		InputToFight = InputActionFight.Object;
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
		EnhancedInputComponent->BindAction(InputToRoll, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputRoll);
		EnhancedInputComponent->BindAction(InputToFight, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputFight);
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
		AddMovementInput(ForwardDirection, MovementVector.Y*0.1);
		AddMovementInput(RightDirection, MovementVector.X*0.1);
	}
}

void ADogCharacter::EnhancedInputLook(const FInputActionValue& Value){
	FVector2D LookVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr){
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
	
}
//공격 모션 12번째 트라이
void ADogCharacter::EnhancedInputFight(const FInputActionValue& Value){
	bool v = Value.Get<bool>();

	PressAtk();
}

void ADogCharacter::PressAtk()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(animInstance->IsAnyMontagePlaying()){
		return; //이미 공격중에는 연속 입력이 안되기 위함 
	}
	animInstance->Montage_Play(AttackMontage);
}

void ADogCharacter::EnhancedInputRoll(const FInputActionValue& Value){
	FVector CurrentVelocity = GetVelocity(); //ACharacter 함수

	if(CurrentVelocity.Size()){
		LaunchCharacter(CurrentVelocity*5, false, false);
	}
	else { //제자리에서 깡총깡총
		LaunchCharacter(FVector(0, -10, 0), true, false);
	}
}
