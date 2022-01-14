// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonGun.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonCharacter.h"

// Sets default values
AThirdPersonGun::AThirdPersonGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	RapidAmmo	= RapidAmmoMax;

}

void AThirdPersonGun::SingleFire()
{
	//Initialise Viewport Variables
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector		ViewLocation;
	FRotator	ViewRotation;

	//Initialise LineTrace Variablesw
	FHitResult HitResult;
	FVector LineTraceEnd;
	bool bObjectHit;

	OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	//Work out end of line trace
	LineTraceEnd = ViewLocation + ViewRotation.Vector() * Range;
	//Perform line trace store hit object in HitResult

	FCollisionQueryParams Params;			// Line trace parameters
	Params.AddIgnoredActor(this);			// Ignore the gun
	Params.AddIgnoredActor(GetOwner());		// Ignore the owner of the gun

	bObjectHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2, Params);

	//If an object was hit 
	if (bObjectHit)
	{
		//Get the actor from the hit result so that a take damage function can be called
		AActor* ActorHit = HitResult.GetActor();

		if (ActorHit != nullptr)
		{
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
			UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());
		}
	}

	SingleAmmo--;
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
		case 0:
			GrenadeAmmo = GrenadeAmmoMax;
		break;

		case 1:
			SingleAmmo = SingleAmmoMax;
		break;

		case 2:
			//Machine gun
		break;
	}
}

void AThirdPersonGun::RapidFire()
{
	if (bFiring)
	{
		//Initialise Viewport Variables
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		AController* OwnerController = OwnerPawn->GetController();
		FVector		ViewLocation;
		FRotator	ViewRotation;

		//Initialise LineTrace Variables
		FHitResult HitResult;
		FVector LineTraceEnd;
		bool bObjectHit;

		OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
		//Work out end of line trace
		LineTraceEnd = ViewLocation + ViewRotation.Vector() * Range;
		//Perform line trace store hit object in HitResult

		bObjectHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2);

		//If an object was hit 
		if (bObjectHit)
		{
			//Get the actor from the hit result so that a take damage function can be called
			AActor* ActorHit = HitResult.GetActor();

			if (ActorHit != nullptr)
			{
				DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
				UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

void AThirdPersonGun::FireGrenade()
{
	FVector SpawnLocation	= ProjectileSpawn->GetComponentLocation();
	FRotator SpawnRotation	= ProjectileSpawn->GetComponentRotation();
	TArray<AActor*> GrenadeCount;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectileGrenade::StaticClass(), GrenadeCount);

		if (GrenadeCount.Num() < 1)
		{
			FiredGrenade = GetWorld()->SpawnActor<AProjectileGrenade>(ProjectileClass, SpawnLocation, SpawnRotation);
			FiredGrenade->SetOwner(GetOwner());
			GrenadeAmmo--;
		}
}

// Called every frame
void AThirdPersonGun::SwitchModeUp()
{
	if (!bReloading)
		Mode++;

	//Mode Wrap around
	if (Mode > 2) Mode = 0;
}

void AThirdPersonGun::SwitchModeDown()
{
	if (!bReloading)
		Mode--;

	//Mode Wrap around
	if (Mode < 0) Mode = 2;
}

void AThirdPersonGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThirdPersonGun::Fire()
{
	/*
		Line trace from player viewport to a location determined by the weapons maximum range
		if an object is hit store it in a FHitResult and apply damage
	*/

	if (!bReloading)
	{
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

		case 2:
			UE_LOG(LogTemp, Warning, TEXT("RapidFire"))
				break;



		}
	}
}
