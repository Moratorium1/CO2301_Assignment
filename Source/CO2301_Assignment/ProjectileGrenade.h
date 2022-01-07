// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileGrenade.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API AProjectileGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileGrenade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	FTimerHandle DetonationTimer;

	UPROPERTY(EditAnywhere)
	float MaxDetonateTime = 3.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 50.0f;

	UPROPERTY(EditAnywhere)
	float MinDamage = 20.0f;

	UPROPERTY(EditAnywhere)
	float InnerDmgRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float OuterDmgRadius = 200.0f;

	UPROPERTY(EditAnywhere)
	float DmgFalloff = 0.5f;

	UFUNCTION()
	void Detonate();
};
