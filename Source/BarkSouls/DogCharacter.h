#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#pragma once

#include "DogCharacter.generated.h"

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

	bool bAttacking;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* AttackMontage;

	void PressAtk();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToMove;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToLook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* InputToFight;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	//class UInputTriggerHold* RunTrigger;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	//class UInputTriggerPressed* RollTrigger;

	void EnhancedInputMove(const FInputActionValue& Value);
	void EnhancedInputLook(const FInputActionValue& Value);
	void EnhancedInputRun(const FInputActionValue& Value);
	void EnhancedInputFight(const FInputActionValue& Value);
};
