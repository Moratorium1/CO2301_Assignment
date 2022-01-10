// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "ThirdPersonAIController.h"

AActor* AThirdPersonAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void AThirdPersonAIController::RandomPatrol()
{
	AActor* ChoosenWaypoint = ChooseWaypoint();
	SetFocus(ChoosenWaypoint);
	MoveToActor(ChoosenWaypoint);
}

void AThirdPersonAIController::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	
	RandomPatrol();
}

void AThirdPersonAIController::OnMoveCompleted(FAIRequestID RequestID, const
	FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	RandomPatrol();
}
