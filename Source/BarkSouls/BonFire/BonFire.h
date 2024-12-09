// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapResetComponent.h"
#include "Bonfire.generated.h"

UCLASS()
class BARKSOULS_API ABonfire : public AActor
{
	GENERATED_BODY()

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

	// ȭ��� ��ġ ������
	static TMap<FName, FTransform> BonfireLocations;

	// ȭ��� ��� ����
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	bool bIsRegistered;

	// ���� ȭ��� ID
	UPROPERTY(EditAnywhere, Category = "Bonfire")
	FName BonfireID;

	// �÷��̾ ���� ���� �ִ��� ����
	UPROPERTY(EditAnywhere, Category = "State")
	bool bPlayerInRange;

	// UI ���� Ŭ����
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBonfireUI> BonfireWidgetClass;

	// ������ UI ���� �ν��Ͻ�
	UPROPERTY()
	class UBonfireUI* BonfireWidget;

private:
	// �ٸ� ȭ��ҷ� �����̵�
	UFUNCTION(BlueprintCallable, Category = "Bonfire")
	void TeleportPlayer(AActor* Player, FName TargetBonfireID);

	// ȭ��� ��ġ ��� -> ȭ��Ұ� ��ȣ�ۿ��� �ؾ��� ID�� ��ϵ�.
	void RegisterBonfireLocation();

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

	// ȭ��� ��ȭ�ۿ�
	UFUNCTION()
	void Interact();

	// �÷��̾�� ��ȣ�ۿ�
	void ShowBonfireUI();
	void HideBonfireUI();

	void ShowMessage(FString Message);

};
