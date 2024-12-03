#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

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


public:
	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* LAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* HAttackMontage;

	void PressAtk(float inputValue);

protected:

	bool bAttacking;

	float walkspeed = 0.25;
	float runspeed = 0.75;
	
	bool bIsRunning = false;
	bool bIsRolling = false;

	float Health;

	float Stamina = 100;
	float stamina_Regain = 0.01;

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


	void EnhancedInputMove(const FInputActionValue& Value);
	void EnhancedInputLook(const FInputActionValue& Value);

	void EnhancedInputRunAndRoll(const FInputActionValue& Value);
	void EnhancedInputRunReleased(const FInputActionValue& Value);

	void EnhancedInputFight(const FInputActionValue& Value);
	void EnhancedInputParry(const FInputActionValue& Value);
	void ParryEnd();
};
