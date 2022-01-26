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

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBarrelFracture(const FVector& HitPoint, const FVector& HitDirection);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ItemToDrop;

};