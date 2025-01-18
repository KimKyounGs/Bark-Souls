// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "BarkSouls/DogCharacter.h"
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

	// UI ���� Ŭ����
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireUI> BonfireWidgetClass;

	// ������ UI ���� �ν��Ͻ�
	UPROPERTY(EditAnywhere, Category = "UI")
	class UBonfireUI* BonfireWidget;

	// Teleport UI Ŭ���� Ÿ��
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireTeleportUI> TeleportUIClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	class UBonfireTeleportUI* TeleportUI;

	ADogCharacter* Player;
	// ���߿� ��ġ��
	APlayerController* PlayerController;

private:
	// ȭ��� ��ġ ��� -> ȭ��Ұ� ��ȣ�ۿ��� �ؾ� ID�� ��ϵ�.
	void RegisterBonfireLocation();
	// UI
	void ShowBonfireUI();
	void HideBonfireUI();

public:
	// ȭ��� ��ġ ������
	static TMap<FName, FBonfireData> StaticActiveBonfires;

	// ȭ��� ��ȭ�ۿ�                   
	UFUNCTION()
	void Interact();

	// UI ��ư�� ����� �Լ���.
	UFUNCTION()
	void OnRest();

	UFUNCTION()
	void OnTeleport();

	UFUNCTION()
	void OnLeave();

	// ����� �� �Լ�
	void ShowMessage(FString Message);
};
