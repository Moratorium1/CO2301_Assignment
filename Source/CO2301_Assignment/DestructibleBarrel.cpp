// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBarrel.h"

ADestructibleBarrel::ADestructibleBarrel()
{

}

void ADestructibleBarrel::BeginPlay()
{
	Super::BeginPlay();

	OnActorFracture.AddDynamic(this, &ADestructibleBarrel::OnBarrelFracture);

}

void ADestructibleBarrel::OnBarrelFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel Broken"));
}
