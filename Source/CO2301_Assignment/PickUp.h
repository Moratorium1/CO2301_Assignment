// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class CO2301_ASSIGNMENT_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	float HealAmount = 40.0f;
};
