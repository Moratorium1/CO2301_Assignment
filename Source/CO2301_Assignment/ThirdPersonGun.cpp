// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "ThirdPersonCharacter.h"
#include "ThirdPersonGun.h"

// Sets default values
AThirdPersonGun::AThirdPersonGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AThirdPersonGun::BeginPlay()
{
	Super::BeginPlay();

	SingleAmmo = SingleAmmoMax;

}

void AThirdPersonGun::BurstFire()
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



	for (int i = 0; i < 3; i++)
	{
		ViewLocation.X += FMath::FRandRange(-Recoil / 2, Recoil / 2);
		ViewLocation.Y += FMath::FRandRange(-Recoil / 2, Recoil / 2);
		ViewLocation.Z += Recoil;
		bObjectHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2);

		//If an object was hit 
		if (bObjectHit)
		{
			//Get the actor from the hit result so that a take damage function can be called
			AActor* ActorHit = HitResult.GetActor();

			if (ActorHit != nullptr)
			{
				DrawDebugPoint(GetWorld(), HitResult.Location, 10, FColor::Red, true);
				UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

void AThirdPersonGun::SingleFire()
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
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
			UGameplayStatics::ApplyDamage(ActorHit, Damage, OwnerController, this, UDamageType::StaticClass());
		}
	}

	SingleAmmo--;
}

void AThirdPersonGun::SingleReload()
{
	AThirdPersonCharacter* OwnerChar = Cast<AThirdPersonCharacter>(GetOwner());
	OwnerChar->bReloading = true;
	UE_LOG(LogTemp, Warning, TEXT("Single Reload"));
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

// Called every frame
void AThirdPersonGun::SwitchModeUp()
{
	Mode++;
}

void AThirdPersonGun::SwitchModeDown()
{
	Mode--;
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

	switch (Mode)
	{
		case 1:
			if (SingleAmmo > 0)
				SingleFire();
			else
				SingleReload();
		break;

		case 2:
			BurstFire();
		break;

		case 3:
			RapidFire();
		break;



	}
}
