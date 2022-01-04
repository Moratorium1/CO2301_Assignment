// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonGun.h"
#include "ThirdPersonCharacter.h"


// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// Spring Arm Variables
	SpringArm->TargetArmLength = 200.0f;

	// Spring Arm Rotation
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bEnableCameraLag = true;

	// Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	ActiveWeapon = GetWorld()->SpawnActor<AThirdPersonGun>(WeaponClass);
	ActiveWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));
	ActiveWeapon->SetOwner(this);
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
	ActiveWeapon->Fire();
}

float AThirdPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);

	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	return DamageApplied;
}


