// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonCharacter.generated.h"

class AThirdPersonGun;

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Variable")
	bool Ironsight;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Variable")
	bool bReloading;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Variable")
	bool bIsDead = false;

	// Player Controls
	void MoveForwards(float AxisAmount);
	void Strafe(float AxisAmount);
	void Lookup(float AxisAmount);
	void Turn(float AxisAmount);
	virtual void Jump() override;
	void StartCrouch();
	void EndCrouch();
	void StartIronSight();
	void EndIronSight();
	void FireWeapon();
	void SwitchWeaponUp();
	void SwitchWeaponDown();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AThirdPersonGun> WeaponClass;

	UPROPERTY()
	AThirdPersonGun* ActiveWeapon;

	UPROPERTY(VisibleAnywhere)
	float Health = 100.0f;

};
