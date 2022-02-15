// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonGun.h"
#include "Components/CapsuleComponent.h"
#include "ThirdPersonController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPersonGameMode.h"
#include "Components/SceneCaptureComponent2D.h"

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

	// MiniMap SpringArm
	MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap Spring Arm"));
	MiniMapSpringArm->SetupAttachment(RootComponent);

	// Create MiniMap Cam
	MiniMapCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap"));
	MiniMapCam->SetupAttachment(MiniMapSpringArm);
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the wepaon and attach it to the characters hand socket set its owner to this character
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
	AddMovementInput(GetActorForwardVector(), AxisAmount);
}

void AThirdPersonCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector(), AxisAmount);
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
	if (!bReloading)
		Ironsight = true;
}

void AThirdPersonCharacter::EndIronSight()
{
	if (!bReloading)
		Ironsight = false;
}

void AThirdPersonCharacter::FireWeapon()
{
	ActiveWeapon->Fire();
}

void AThirdPersonCharacter::SwitchWeapon()
{
	/* If the character is not reloading call the switch mode function of the weapon */
	if (!bReloading)
		ActiveWeapon->SwitchMode();
}

void AThirdPersonCharacter::ReloadWeapon()
{
	/* If the character is not reloading call the switch mode function of the weapon */
	if (!bReloading)
		ActiveWeapon->ReloadStart();
}

bool AThirdPersonCharacter::HasDied()
{
	return Health <= 0;
}

float AThirdPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//Damage is clamped so that it cannot be greater than the remaining health of the character and then applied
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	
	//If HasDied returns true the character has died 
	if (HasDied())
	{
		bIsDead = true;		//bIsDead set to true this variable is used for animation purposes

		//Get the GameMode and if not nullptr call the PawnKilledMethod
		AThirdPersonGameMode* GameMode = Cast<AThirdPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode != nullptr)
			GameMode->PawnKilled(this);

		//Dettaching the controller prevents the controllers controlling their characters - AI Pawns stop moving after death
		//Setting capsule components to NoCollision allows the player to walk over and shoot through dead enemies
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

float AThirdPersonCharacter::GetHealthPercentage() const
{
	return Health / HealthMax;
}


