#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

#pragma once

#include "DogCharacter.generated.h"

UENUM(BlueprintType)
enum class EState : uint8
{
	Ready UMETA(DisplayName="Ready"),
	Run UMETA(DisplayName="Run"),
	Roll UMETA(DisplayName="Roll"),
	Walk UMETA(DisplayName="Walk"),
	Attack UMETA(DisplayName="Attack"),
	Parry UMETA(DisplayName="Parry"),
	Dead UMETA(DisplayName="Dead")
};

UCLASS()
class BARKSOULS_API ADogCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADogCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FName currentBonfireID;

public:
	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* LAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* HAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* RollingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* ParryMontage;

	void PressAtk(float inputValue);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack")
	class UBoxComponent* AttackHitBox;


protected:
	float walkspeed = 0.5f;
	float runspeed = 1.0f;

	float Health = 100.0f;

	float Stamina = 100.0f;
	float stamina_Regain = 0.01f;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
	EState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToMove;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToLook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToRunAndRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToFight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToParry;

	//상태 관리
	void SetCharacterState(EState NewState);
	
	//이동 관련 함수
	void EnhancedInputMove(const FInputActionValue& Value); //Move
	void EnhancedInputWalkReleased(const FInputActionValue& Value); //Move Release
	void EnhancedInputLook(const FInputActionValue& Value); //Look
	void EnhancedInputRunAndRoll(const FInputActionValue& Value); //Run and Roll
	void EnhancedInputRunReleased(const FInputActionValue& Value); //Run End

	//전투 관련 함수
	void EnhancedInputFight(const FInputActionValue& Value); //Attack
	void EnhancedInputParry(const FInputActionValue& Value); //Parrying
	void ParryEnd(); //Timer callback 

	UFUNCTION()
	void OnAttackHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EnableAttackHitBox();
	UFUNCTION()
	void DisableAttackHitBox();

	//데미지 시스템
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	// 화톳불 관련 함수
	// 최근 화톳불 ID 저장 함수
	void SetCurrentBonfireID(const FName BonfireID);

	void TeleportPlayer(const FTransform TargetTransform);
};
