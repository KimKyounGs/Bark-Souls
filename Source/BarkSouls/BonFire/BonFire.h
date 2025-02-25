// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "BonfireTypes.h"
#include "Bonfire.generated.h"

UCLASS()
class BARKSOULS_API ABonfire : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ABonfire();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
private:
	// ȭ��� �޽�
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* BonfireMesh;

	// ȭ��� �ݸ��� �ڽ�
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* InteractionBox;

	// �� ���� ������Ʈ
	UPROPERTY(EditAnywhere, Category = "Component")
	class UMapResetComponent* MapResetComponent;

	// ȭ��� ������
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FBonfireData BonfireData;

	// �÷��̾ ���� ���� �ִ��� ����
	UPROPERTY(EditAnywhere, Category = "State")
	bool bPlayerInRange;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bUsingBonfire;

	// ���̾ư��� ����Ʈ
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraComponent* BonfireEffect; // �Ҳ� ����Ʈ

	// ���� ���� �߰�
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* BonfireIgniteSound; // �Ҳ� ��ȭ ���� (�� ���� ���)

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* BonfireLoopSound;   // ���ӵǴ� ȭ��� ���� (�ݺ� ���)

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundAttenuation* BonfireSoundAttenuation; // ���״����̼� ����

	UPROPERTY()
	class UAudioComponent* BonfireLoopAudioComponent; //�ݺ� ����� ���� ����� ������Ʈ

	APlayerController* PlayerController;

private:


public:

	// ȭ��� ��ȭ�ۿ�                   
	UFUNCTION()
	void Interact();

	// ����� �� �Լ�
	void ShowMessage(FString Message);
};
