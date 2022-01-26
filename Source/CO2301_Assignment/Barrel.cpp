// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BarrelMesh->SetupAttachment(RootComponent);
	BarrelMesh->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ABarrel::HandleHit);
	
}

void ABarrel::HandleHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("** Barrel Hit by: %s!"), *OtherActor->GetName());
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

