// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonCharacter.generated.h"

class AThirdPersonGun;
class USceneCaptureComponent2D;

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

	// Variables used by the character animation blueprint
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation")
	bool Ironsight;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation")
	bool bReloading;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere)
	float Health = 100.0f;

	UFUNCTION()
	bool HasDied();

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
	void SwitchWeapon();
	void ReloadWeapon();

	// Active weapon made piblic to allow for pickup interaction
	UPROPERTY(BlueprintReadOnly)
	AThirdPersonGun* ActiveWeapon;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Used by widget to determine % health to show health bar
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	UPROPERTY(VisibleAnywhere, Category = "MiniMap")
	class USpringArmComponent* MiniMapSpringArm;

	UPROPERTY(EditAnywhere, Category = "MiniMap")
	USceneCaptureComponent2D* MiniMapCam;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AThirdPersonGun> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	float HealthMax = 100.0f;
};
