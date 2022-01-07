// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ProjectileGrenade.h"

// Sets default values
AProjectileGrenade::AProjectileGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void AProjectileGrenade::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DetonationTimer, this, &AProjectileGrenade::Detonate, MaxDetonateTime, false);
}

void AProjectileGrenade::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(DetonationTimer);
}

void AProjectileGrenade::Detonate()
{
	UE_LOG(LogTemp, Warning, TEXT("Detonate"));
	TArray<AActor*> IgnoreActors;
	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), Damage, MinDamage, GetActorLocation(), InnerDmgRadius, OuterDmgRadius, DmgFalloff, UDamageType::StaticClass(), IgnoreActors, this, GetOwner()->GetInstigatorController(), ECollisionChannel::ECC_EngineTraceChannel2);
	Destroy();
}

// Called every frame
void AProjectileGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

