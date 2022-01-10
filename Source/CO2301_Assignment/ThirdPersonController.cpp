// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonController.h"
#include "ThirdPersonCharacter.h"


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

	InputComponent->BindAction("SwitchUp",	IE_Pressed,		this, &AThirdPersonController::CallSwitchWeaponUp);
	InputComponent->BindAction("SwitchDown", IE_Pressed,	this, &AThirdPersonController::CallSwitchWeaponDown);
}

void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = GetPawn();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
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

void AThirdPersonController::CallSwitchWeaponUp()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->SwitchWeaponUp();
	}
}

void AThirdPersonController::CallSwitchWeaponDown()
{
	if (MyPawn->IsA(AThirdPersonCharacter::StaticClass()))
	{
		Cast<AThirdPersonCharacter>(MyPawn)->SwitchWeaponDown();
	}
}