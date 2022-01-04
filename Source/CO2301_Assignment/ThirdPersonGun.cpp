// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
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

}

// Called every frame
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

	//UE_LOG(LogTemp, Warning, TEXT("Fire"));

	//Get player viewport
	FVector		ViewLocation;
	FRotator	ViewRotation;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* OwnerController = OwnerPawn->GetController();
	OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	//Work out end of line trace
	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * Range;

	//Perform line trace store hit object in HitResult
	FHitResult HitResult;
	bool bObjectHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_EngineTraceChannel2);

	//If an object was hit 
	if (bObjectHit)
	{
		//Get the actor from the hit result so that a take damage function can be called
		AActor* ActorHit = HitResult.GetActor();

		//Get shot direction for the point damage event
		FVector DirectionShot = -ViewRotation.Vector();

		if (ActorHit != nullptr)
		{
			DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
			FPointDamageEvent DamageEvent(Damage, HitResult, DirectionShot, nullptr);
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}


}
