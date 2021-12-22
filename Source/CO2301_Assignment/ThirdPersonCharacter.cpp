// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonGun.h"
#include "ThirdPersonCharacter.h"


// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThirdPersonCharacter::MoveForwards(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount);
}

void AThirdPersonCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

void AThirdPersonCharacter::Lookup(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void AThirdPersonCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

void AThirdPersonCharacter::Jump()
{
	Super::Jump();

}

void AThirdPersonCharacter::StartCrouch()
{
	Crouch();
}

void AThirdPersonCharacter::EndCrouch()
{
	UnCrouch();
}

void AThirdPersonCharacter::StartIronSight()
{
	Ironsight = true;
}

void AThirdPersonCharacter::EndIronSight()
{
	Ironsight = false;
}

void AThirdPersonCharacter::FireWeapon()
{
	//ActiveWeapon->Fire();
}
