// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBarrel.h"
#include "PickUp.h"
#include "Kismet/GameplayStatics.h"

ADestructibleBarrel::ADestructibleBarrel()
{
	ItemSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ItemSpawn"));
	ItemSpawn->SetupAttachment(RootComponent);
}

void ADestructibleBarrel::BeginPlay()
{
	Super::BeginPlay();

	OnActorFracture.AddDynamic(this, &ADestructibleBarrel::OnBarrelFracture);
}

void ADestructibleBarrel::OnBarrelFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	TArray<AActor*> IgnoreActors;
	if (bIsExplosive)	//If bIsExplosive is set to true apply damage in a radius 
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), Damage, MinDamage, GetActorLocation(), InnerDmgRadius, OuterDmgRadius, DmgFalloff, UDamageType::StaticClass(), IgnoreActors, this, GetInstigatorController(), ECollisionChannel::ECC_EngineTraceChannel2);

	// Spawn any item set to drop by the fractured actor
	FVector ActorLocation = GetActorLocation();
	FVector SpawnLocation = FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z + ItemSpawnZOffset);
	GetWorld()->SpawnActor<APickUp>(ItemToDrop, SpawnLocation, FRotator::ZeroRotator);
}
