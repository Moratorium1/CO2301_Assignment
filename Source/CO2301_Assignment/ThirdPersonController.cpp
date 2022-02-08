// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonController.h"
#include "ThirdPersonCharacter.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the pawn being controlled
	MyPawn = GetPawn();

	// Add the HUD tp the players viewport
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void AThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForwards", this, &AThirdPersonController::CallMoveForwards);
	InputComponent->BindAxis("Strafe",		 this, &AThirdPersonController::CallStrafe);
	InputComponent->BindAxis("LookUp",		 this, &AThirdPersonController::CallLookup);
	InputComponent->BindAxis("Turn",		 this, &AThirdPersonController::CallTurn);

	InputComponent->BindAction("Jump",		IE_Pressed,		this, &AThirdPersonController::CallJump);
	InputComponent->BindAction("Crouch",	IE_Pressed,		this, &AThirdPersonController::CallStartCrouch);
	InputComponent->BindAction("Crouch",	IE_Released,	this, &AThirdPersonController::CallEndCrouch);
	InputComponent->BindAction("Ironsight", IE_Pressed,		this, &AThirdPersonController::CallStartIronSight);
	InputComponent->BindAction("Ironsight", IE_Released,	this, &AThirdPersonController::CallEndIronSight);
	InputComponent->BindAction("Fire",		IE_Pressed,		this, &AThirdPersonController::CallFireWeapon);

	InputComponent->BindAction("Switch",	IE_Pressed,		this, &AThirdPersonController::CallSwitchWeapon);
}

void AThirdPersonController::CallMoveForwards(float AxisAmount)
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->MoveForwards(AxisAmount);
	}
}

void AThirdPersonController::CallStrafe(float AxisAmount)
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->Strafe(AxisAmount);
	}
}

void AThirdPersonController::CallLookup(float AxisAmount)
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->Lookup(AxisAmount);
	}
}

void AThirdPersonController::CallTurn(float AxisAmount)
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->Turn(AxisAmount);
	}
}

void AThirdPersonController::CallJump()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->Jump();
	}
}

void AThirdPersonController::CallStartCrouch()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->StartCrouch();
	}
}

void AThirdPersonController::CallEndCrouch()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->EndCrouch();
	}
}

void AThirdPersonController::CallStartIronSight()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->StartIronSight();
	}
}

void AThirdPersonController::CallEndIronSight()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->EndIronSight();
	}
}

void AThirdPersonController::CallFireWeapon()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->FireWeapon();
	}
}

void AThirdPersonController::CallSwitchWeapon()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->SwitchWeapon();
	}
}

void AThirdPersonController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{	// Called when the game has ended, either via player death or all enemies have been killed
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// Start a timer for 5 seconds to restart the game
	GetWorldTimerManager().SetTimer(RestartTimer, this, &AThirdPersonController::RestartLevel, RestartTime);

	// Show either the win or lose HUD
	if (!bIsWinner)
	{
		LoseHUD = CreateWidget(this, LoseHUDClass);
		if (LoseHUD != nullptr)
		{
			LoseHUD->AddToViewport();
		}
	}
	else
	{
		WinHUD = CreateWidget(this, WinHUDClass);
		if (WinHUD != nullptr)
		{
			WinHUD->AddToViewport();
		}
	}

}

void AThirdPersonController::RestartLevel()
{
	Super::RestartLevel();
}