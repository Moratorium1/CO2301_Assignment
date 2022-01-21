// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPersonAIController.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonAIController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> PatrolPoints;

	UFUNCTION()
	bool PlayerSeen();

	UFUNCTION()
	virtual void BeginPlay() override;

	bool HasDied() const;

private:
	
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Waypoints;

	UPROPERTY()
	APawn* PlayerPawn;

	UFUNCTION()
	bool IsPlayerInFront();

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UFUNCTION()
	void GetPatrolPoints();

};
