// Fill out your copyright notice in the Description page of Project Settings.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

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

	//컨트롤러 방향에 회전하지 않도록
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//springArm
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);

	springArmComp->bUsePawnControlRotation = true;
	springArmComp->TargetArmLength = 250;
	springArmComp->SetRelativeLocation(FVector(0, 25, 0)); 
	
	//Camera
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;

	//Character Setup
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 인풋에 의해 방향을 정의하도록	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 회전 속도 

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
	UE_LOG(LogTemp, Display, TEXT("Stamina: %f"), Stamina);
	if(Stamina < 100.f){
		Stamina += stamina_Regain;
	}
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
	
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Forward 및 Right 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y*walkspeed);
		AddMovementInput(RightDirection, MovementVector.X*walkspeed);
	}
}

void ADogCharacter::EnhancedInputLook(const FInputActionValue& Value){
	FVector2D LookVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr){
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
	// if (springArmComp != nullptr){ // 최후의 수단 -> 그냥 카메라가 회전을 안함 ㅋㅋ
	// 	FRotator NewRotation = springArmComp->GetRelativeRotation(); 
    //     NewRotation.Yaw += LookVector.X;
    //     NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + LookVector.Y, -80.0f, 80.0f); // Pitch 제한
    //     springArmComp->SetRelativeRotation(NewRotation);
	// }
		
}
//공격 모션 12번째 트라이
void ADogCharacter::EnhancedInputFight(const FInputActionValue& Value){
	float inputValue = Value.Get<float>();
	UE_LOG(LogTemp, Display, TEXT("Input Value: %f"), inputValue); //부정을 통해 오른쪽 왼쪽 값 분리함

	PressAtk(inputValue);
}

void ADogCharacter::PressAtk(float inputValue)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(animInstance->IsAnyMontagePlaying()){
		return; // 이미 공격중에는 연속 입력이 안되기 위함 
	}
	if(inputValue == 1.0f && Stamina >= 10.f){
		animInstance->Montage_Play(LAttackMontage); // 좌 클릭 시 약 공격
		Stamina -= 10.f;
	}
	else if(inputValue == -1.0f && Stamina >= 20.f){
		animInstance->Montage_Play(HAttackMontage); // 우 클릭 시 강 공격
		Stamina -= 20.f;
	}
	//else{}
}

void ADogCharacter::EnhancedInputRoll(const FInputActionValue& Value){
	FVector CurrentVelocity = GetVelocity(); //ACharacter 함수
	UE_LOG(LogTemp, Display, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
	UE_LOG(LogTemp, Display, TEXT("Speed: %f"), CurrentVelocity.Size()); //정상적으로 0 출력됨 문제 확인해 볼 것

	if(CurrentVelocity.Size()){
		LaunchCharacter(CurrentVelocity*5, false, false);
	}
	else { //제자리에서 깡총깡총
		LaunchCharacter(FVector(0, -10, 0), true, false);
	}
}
