// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonGun.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();
	void SwitchModeUp();
	void SwitchModeDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void SingleFire();
	void SingleReload();
	void BurstFire();
	void RapidFire();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY()
	int Mode = 1;

	

	UPROPERTY()
	bool bFiring;

	//SingleFireStats
	UPROPERTY(EditAnywhere)
	int SingleAmmoMax = 10;

	UPROPERTY(EditAnywhere)
	int SingleAmmo;

	UPROPERTY(EditAnywhere)
	float Range = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere)
	float Recoil = 30.0f;
	
};
