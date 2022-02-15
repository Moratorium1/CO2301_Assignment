// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonGun.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DestructibleComponent.h"

// Sets default values
AThirdPersonGun::AThirdPersonGun()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AThirdPersonGun::BeginPlay()
{
	Super::BeginPlay();

	SingleAmmo	= SingleAmmoMax;
	GrenadeAmmo = GrenadeAmmoMax;
}



void AThirdPersonGun::ReloadStart()
{
	AThirdPersonCharacter* OwnerChar = Cast<AThirdPersonCharacter>(GetOwner());		// Get a Reference to the character
	OwnerChar->bReloading = true;													// Set the character reloading bool to true - For animation purposes
	bReloading = true;																// Set the weapons reloading bool to true	- To prevent firing and mode switching
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AThirdPersonGun::ReloadEnd, MaxReloadTime, false);	// Set a Timer at the end which ReloadEnd is called
}

void AThirdPersonGun::Resupply()
{
	SingleAmmo = SingleAmmoMax;
	GrenadeAmmo = GrenadeAmmoMax;
}


void AThirdPersonGun::ReloadEnd()
{
	AThirdPersonCharacter* OwnerChar = Cast<AThirdPersonCharacter>(GetOwner());		// Get a Reference to the character
	OwnerChar->bReloading = false;
	bReloading = false;
	
	switch (Mode)	// Set the Ammo of the mode the player was in to max
	{
		case EWEAPONMODE::GRENADE:
			GrenadeAmmo = GrenadeAmmoMax;
		break;

		case EWEAPONMODE::DEFAULT:
			SingleAmmo = SingleAmmoMax;
		break;
	}
}

// Called every frame
void AThirdPersonGun::SwitchMode()
{
	/* If the character is not reloading swap from the current mode to the other */
	if (!bReloading)
		switch (Mode)
		{
			case EWEAPONMODE::GRENADE:
			Mode = EWEAPONMODE::DEFAULT;
			break;

			case EWEAPONMODE::DEFAULT:
			Mode = EWEAPONMODE::GRENADE;
			break;
		}
}

void AThirdPersonGun::Fire()
{
	// Call a weapon fire function dependent on Mode if the character is not reloading else reload the weapon
	if (!bReloading)
	{
		switch (Mode)
		{
		case EWEAPONMODE::GRENADE:
			if (GrenadeAmmo > 0)
				FireGrenade();
			else
				ReloadStart();
			break;

		case EWEAPONMODE::DEFAULT:
			if (SingleAmmo > 0)
				SingleFire();
			else
				ReloadStart();
			break;
		}
	}
}

void AThirdPersonGun::SingleFire()
{
	// Reduce Single Fire Weapon Ammo
	SingleAmmo--;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlash, ProjectileSpawn->GetComponentLocation(), ProjectileSpawn->GetComponentRotation(), FVector(1), false, true);

	// Get the pawn to get the controller to then get the viewport
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	// Get the view loaction and rotation
	FVector		ViewLocation;
	FRotator	ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	
	// Set Parameters of the LineTrace
	FCollisionQueryParams Params;											// Line trace parameters
	Params.AddIgnoredActor(this);											// Ignore the gun
	Params.AddIgnoredActor(GetOwner());										// Ignore the owner of the gun
	FVector	LineTraceEnd = ViewLocation + ViewRotation.Vector() * Range;	// Workout where to end the LineTrace
	
	// Play Weapon Fire sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFired, GetActorLocation());

	// Performing a line trace returns a bool & stores infomation about object hit in HitResult
	FHitResult	HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2, Params))
	{
		//Get the actor from the hit result so that a take damage function can be called
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit == nullptr)
			return;

		// Impact Particle System should be spawned to face towards the direction shot from or the reverse of the Rotation the gun that fired
		FRotator GunRotation = GetActorRotation();
		FRotator ImpactRotation = FRotator(-GunRotation.Pitch, -GunRotation.Yaw, -GunRotation.Roll);

		// Apply damage and spawn impact particle system
		UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlash, ActorHit->GetActorLocation(), ImpactRotation, FVector(ImpactParticleScale), false, true);

		// Apply Force to StaticMesh components
		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitResult.Component);
		if (MeshComponent && ActorHit->IsRootComponentMovable())
		{
			FVector Forwards = this->GetActorForwardVector();
			MeshComponent->AddImpulse(-Forwards * Force * MeshComponent->GetMass());
		}

		// Apply Force to DestrucibleMesh components
		UDestructibleComponent* DestructibleMesh = Cast<UDestructibleComponent>(HitResult.Component);
		if (DestructibleMesh && ActorHit->IsRootComponentMovable())
		{
			FVector Forwards = this->GetActorForwardVector();
			DestructibleMesh->AddImpulse(-Forwards * Force * DestructibleMesh->GetMass());
		}
	}
}

void AThirdPersonGun::FireGrenade()
{
	// Get ProjectileSpawn location and Rotation
	FVector SpawnLocation = ProjectileSpawn->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawn->GetComponentRotation();

	// Create an array and fill it with all the actors of the AProjectileGrenades class currently in the world.
	TArray<AActor*> GrenadeCount;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectileGrenade::StaticClass(), GrenadeCount);

	// Only fire a grenade if there less grenade actors in the world than the maximum grenade count value - default is 1.
	if (GrenadeCount.Num() < MaxGrenadeCount)	
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlash, ProjectileSpawn->GetComponentLocation(), ProjectileSpawn->GetComponentRotation(), FVector(1), false, true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GrenadeLaunched, GetActorLocation());						// Play Grenade Launched sound
		FiredGrenade = GetWorld()->SpawnActor<AProjectileGrenade>(ProjectileClass, SpawnLocation, SpawnRotation);	// Spawn the Grenade
		FiredGrenade->SetOwner(GetOwner());									// Set the Owner of the grenade to the owner of the gun - could use to disable friendly fire
		GrenadeAmmo--;														// Decrement grenade Ammo
	}
}