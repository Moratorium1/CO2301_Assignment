// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ThirdPersonController.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	virtual void RestartLevel() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	float RestartTime = 5.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseHUDClass;

	UUserWidget* LoseHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinHUDClass;

	UUserWidget* WinHUD;

	// Player Control Functions

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
	void CallSwitchWeapon();
	void CallReload();

};
