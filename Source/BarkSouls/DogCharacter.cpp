// Fill out your copyright notice in the Description page of Project Settings.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DB.h"

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
	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionRunAndRoll(TEXT("/Game/Kwanik/Input/IA_RunAndRoll.IA_RunAndRoll"));
	if(InputActionRunAndRoll.Succeeded()){
		InputToRunAndRoll = InputActionRunAndRoll.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionFight(TEXT("/Game/Kwanik/Input/IA_Fight.IA_Fight"));
	if(InputActionFight.Succeeded()){
		InputToFight = InputActionFight.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionParry(TEXT("/Game/Kwanik/Input/IA_Parry.IA_Parry"));
	if(InputActionParry.Succeeded()){
		InputToParry = InputActionParry.Object;
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

	//Initialize State
	CharacterState = EState::Ready;

	//HitBox Initialize
	AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBox"));
	//AttackHitBox->SetupAttachment(GetMesh(), FName("ForwardLeg")); 
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision); //기본: 비활성화
	AttackHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackHitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
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
	//HitBox Overlap Event Bind
	AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &ADogCharacter::OnAttackHitBoxBeginOverlap);
}

// Called every frame
void ADogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Display, TEXT("Stamina: %f"), Stamina);
	if(CharacterState == EState::Run && Stamina > 0.0f){
		Stamina -= stamina_Regain;
		if(Stamina <= 0.0f) {
			SetCharacterState(EState::Walk);
		}
	}else if(Stamina < 100.f){
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
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Completed, this, &ADogCharacter::EnhancedInputWalkReleased);
		EnhancedInputComponent->BindAction(InputToLook, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputLook);
		EnhancedInputComponent->BindAction(InputToRunAndRoll, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputRunAndRoll);
		EnhancedInputComponent->BindAction(InputToRunAndRoll, ETriggerEvent::Completed, this, &ADogCharacter::EnhancedInputRunReleased);
		EnhancedInputComponent->BindAction(InputToFight, ETriggerEvent::Triggered, this, &ADogCharacter::EnhancedInputFight);
	}
}

void ADogCharacter::SetCharacterState(EState NewState){
	CharacterState = NewState;
}

void ADogCharacter::EnhancedInputMove(const FInputActionValue& Value){
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr && CharacterState != EState::Attack)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Forward 및 Right 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		float CurrentSpeed = (CharacterState == EState::Run) ? runspeed : walkspeed;
		AddMovementInput(ForwardDirection, MovementVector.Y * CurrentSpeed);
        AddMovementInput(RightDirection, MovementVector.X * CurrentSpeed);
	}
}
void ADogCharacter::EnhancedInputWalkReleased(const FInputActionValue& Value){
	SetCharacterState(EState::Ready);
}
void ADogCharacter::EnhancedInputRunAndRoll(const FInputActionValue& Value){
	FVector CurrentVelocity = GetVelocity(); //ACharacter 함수
	// UE_LOG(LogTemp, Display, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
	// UE_LOG(LogTemp, Display, TEXT("Speed: %f"), CurrentVelocity.Size()); //정상적으로 0 출력됨 문제 확인해 볼 것

	if(CharacterState == EState::Ready || CharacterState == EState::Walk){ //구르기
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if(animInstance->IsAnyMontagePlaying()){
			return; // 이미 공격중에는 연속 입력이 안되기 위함 
		}
		SetCharacterState(EState::Roll);
		if(CurrentVelocity.Size()){
			LaunchCharacter(CurrentVelocity*5, false, false);
			animInstance->Montage_Play(RollingMontage);
		}
		else { //제자리에서 깡총깡총
			LaunchCharacter(FVector(-10, 0, 0), true, false);
		}
		SetCharacterState(EState::Run);
	}
	
	
}
void ADogCharacter::EnhancedInputRunReleased(const FInputActionValue& Value){
	SetCharacterState(EState::Ready);
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
	float inputValue = Value.Get<float>();
	// UE_LOG(LogTemp, Display, TEXT("Input Value: %f"), inputValue); //부정을 통해 오른쪽 왼쪽 값 분리함

	PressAtk(inputValue);
	DisableAttackHitBox();
	SetCharacterState(EState::Ready);
}
void ADogCharacter::PressAtk(float inputValue)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if(animInstance->IsAnyMontagePlaying()){
		return; // 이미 공격중에는 연속 입력이 안되기 위함 
	}
	SetCharacterState(EState::Attack);
	if(inputValue == 1.0f && Stamina >= 10.f){
		animInstance->Montage_Play(LAttackMontage); // 좌 클릭 시 약 공격
		Stamina -= 10.f;

		EnableAttackHitBox();
	}
	else if(inputValue == -1.0f && Stamina >= 20.f){
		animInstance->Montage_Play(HAttackMontage); // 우 클릭 시 강 공격
		Stamina -= 20.f;

		EnableAttackHitBox();
	}
}

void ADogCharacter::EnhancedInputParry(const FInputActionValue& Value){
	CharacterState = EState::Parry;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADogCharacter::ParryEnd, 0.3f, false);
	//패링 성공시 코드 추가  
}

void ADogCharacter::ParryEnd(){
	CharacterState = EState::Ready;
}

float ADogCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= ActualDamage;

	if(Health <= 0.0f){
		SetCharacterState(EState::Dead);
	}

	return ActualDamage;
}

void ADogCharacter::EnableAttackHitBox(){
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
void ADogCharacter::DisableAttackHitBox(){
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ADogCharacter::OnAttackHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if(OtherActor && OtherActor != this){
		UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetController(), this, nullptr);
		UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *OtherActor->GetName());
	}
}

void ADogCharacter::SetCurrentBonfireID(const FName BonfireID)
{
	currentBonfireID = BonfireID;
}

void ADogCharacter::TeleportPlayer(const FTransform TargetTransform)
{
	// 위치 설정
	SetActorLocation(TargetTransform.GetLocation());

	// 회전 설정
	SetActorRotation(TargetTransform.GetRotation().Rotator());
}