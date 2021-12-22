// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonGun.h"

// Sets default values
AThirdPersonGun::AThirdPersonGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}
