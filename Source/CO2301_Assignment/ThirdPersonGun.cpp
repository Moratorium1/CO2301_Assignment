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
	AThirdPersonCharacter* OwnerChar = Cast<AThirdPersonCharacter>(GetOwner());
	OwnerChar->bReloading = true;
	bReloading = true;
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AThirdPersonGun::ReloadEnd, MaxReloadTime, false);
}


void AThirdPersonGun::ReloadEnd()
{
	AThirdPersonCharacter* OwnerChar = Cast<AThirdPersonCharacter>(GetOwner());
	OwnerChar->bReloading = false;
	bReloading = false;
	
	switch (Mode)
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
	/*
		Line trace from player viewport to a location determined by the weapons maximum range
		if an object is hit store it in a FHitResult and apply damage
	*/

	if (!bReloading)
	{
		//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlash, ProjectileSpawn, ProjectileSpawn->GetComponentLocation(), ProjectileSpawn->GetComponentRotation(), FVector(1), false, true, ENCPoolMethod::AutoRelease, true);
								 //SpawnSystemAtLocation(const UObject * WorldContextObject, UNiagaraSystem * SystemTemplate, FVector SpawnLocation, FRotator SpawnRotation, FVector Scale, bool bAutoDestroy, bool bAutoActivate, ENCPoolMethod PoolingMethod, bool bPreCullCheck)

		switch (Mode)
		{
		case 0:
			if (GrenadeAmmo > 0)
				FireGrenade();
			else
				ReloadStart();
			break;

		case 1:
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
	
	FHitResult	HitResult;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFired, GetActorLocation());

	// Performing a line trace returns a bool & stores infomation about object hit in HitResult
	if (GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2, Params))
	{
		//Get the actor from the hit result so that a take damage function can be called
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit == nullptr)
			return;

		UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());

		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitResult.Component);
		if (MeshComponent && ActorHit->IsRootComponentMovable())
		{
			FVector Forwards = this->GetActorForwardVector();
			MeshComponent->AddImpulse(-Forwards * Force * MeshComponent->GetMass());
		}

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
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GrenadeLaunched, GetActorLocation());						// Play Grenade Launched sound
		FiredGrenade = GetWorld()->SpawnActor<AProjectileGrenade>(ProjectileClass, SpawnLocation, SpawnRotation);	// Spawn the Grenade
		FiredGrenade->SetOwner(GetOwner());									// Set the Owner of the grenade to the owner of the gun - could use to disable friendly fire
		GrenadeAmmo--;														// Decrement grenade Ammo
	}
}