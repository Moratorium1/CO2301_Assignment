// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "DestructibleBarrel.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API ADestructibleBarrel : public ADestructibleActor
{
	GENERATED_BODY()

public:
	ADestructibleBarrel();

	UPROPERTY(EditInstanceOnly, Category = "Dropped Item")
	USceneComponent* ItemSpawn;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()		// Function called when barrel fractures
	void OnBarrelFracture(const FVector& HitPoint, const FVector& HitDirection);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ItemToDrop;

	UPROPERTY(EditAnywhere)
	float ItemSpawnZOffset = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	bool bIsExplosive = false;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	float Damage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	float MinDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	float InnerDmgRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	float OuterDmgRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosive")
	float DmgFalloff = 0.5f;
};
