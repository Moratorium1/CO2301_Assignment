// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonController.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	virtual void SetupInputComponent() override;

	UPROPERTY()
	class APawn* MyPawn;

	void CallMoveForwards(float AxisAmount);
	void CallStrafe(float AxisAmount);
	void CallLookup(float AxisAmount);
	void CallTurn(float AxisAmount);
	void CallJump();
	void CallStartCrouch();
	void CallEndCrouch();
	void CallStartIronSight();
	void CallEndIronSight();
	void CallFireWeapon();

};
