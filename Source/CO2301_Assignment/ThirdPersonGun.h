// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileGrenade.h"
#include "ThirdPersonGun.generated.h"

class UNiagaraSystem;

UENUM()
enum class EWEAPONMODE : uint8
{
	GRENADE,
	DEFAULT
};

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonGun();

	void Fire();
	void SwitchMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void FireGrenade();
	void SingleFire();
	void ReloadStart();
	void ReloadEnd();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawn;

	UPROPERTY(VisibleAnywhere)
	AProjectileGrenade* FiredGrenade;

	UPROPERTY()
	EWEAPONMODE Mode = EWEAPONMODE::DEFAULT;

	UPROPERTY()
	bool bReloading;

	UPROPERTY()
	FTimerHandle ReloadTimer;

	UPROPERTY(EditAnywhere)
	float MaxReloadTime = 2.15f;

	//SingleFireStats
	UPROPERTY(EditAnywhere)
	int SingleAmmoMax = 10;

	UPROPERTY(EditAnywhere)
	int SingleAmmo;

	//SingleFireStats
	UPROPERTY(EditAnywhere)
	int GrenadeAmmoMax = 3;

	UPROPERTY(EditAnywhere)
	int GrenadeAmmo;

	UPROPERTY(EditAnywhere)
	int MaxGrenadeCount = 1;

	UPROPERTY(EditAnywhere)
	float Range = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere)
	float Force = 1000.0f;

	UPROPERTY(EditAnywhere)
	float Recoil = 30.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileGrenade> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* GrenadeLaunched;

	UPROPERTY(EditAnywhere)
	USoundBase* WeaponFired;
};
