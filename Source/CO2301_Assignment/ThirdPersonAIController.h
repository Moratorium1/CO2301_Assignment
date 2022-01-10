// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ThirdPersonAIController.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonAIController : public AAIController
{
	GENERATED_BODY()

public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	UPROPERTY()
	TArray<AActor*> Waypoints;

	UFUNCTION()
	AActor* ChooseWaypoint();

	UFUNCTION()
	void RandomPatrol();

protected:
	virtual void BeginPlay() override;

};
