// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonGun.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float Range = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;
	
};
