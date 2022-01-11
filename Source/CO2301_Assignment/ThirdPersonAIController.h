// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Waypoints;

private:
	
	UFUNCTION()
	AActor* ChooseWaypoint();

	UPROPERTY()
	APawn* PlayerPawn;

	//UFUNCTION()
	//void RandomPatrol();

	UFUNCTION()
	bool IsPlayerInFront();

	UFUNCTION()
	bool PlayerSeen();

	UFUNCTION()
	void GetWaypoints();

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

protected:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
