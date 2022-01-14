// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "ThirdPersonAIController.h"



void AThirdPersonAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (AIBehavior != nullptr)
		RunBehaviorTree(AIBehavior);

	GetPatrolPoints();
}

void AThirdPersonAIController::GetPatrolPoints()
{
	// Fill the Waypoints array with all target points
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	// Loop through the Waypoints array and filter out any targetpoint with the SpawnPoint Tag
	for (int i = 0; i < Waypoints.Num() - 1; i++)
	{
		if (!Waypoints[i]->ActorHasTag(TEXT("SpawnPoint")))
		{
			PatrolPoints.Add(Waypoints[i]);
		}
	}
}

bool AThirdPersonAIController::IsPlayerInFront()
{
	float DirectionDotProduct;

	APawn* AIPawn = GetPawn();

	FVector AIForwardVector = AIPawn->GetActorForwardVector();
	FVector PlayerPosition = PlayerPawn->GetActorLocation();
	FVector AIPosition = AIPawn->GetActorLocation();
	FVector AIToPlayer = PlayerPosition - AIPosition;
	AIToPlayer.Normalize();
	DirectionDotProduct = FVector::DotProduct(AIToPlayer, AIForwardVector);

	return (DirectionDotProduct > 0);
}

bool AThirdPersonAIController::PlayerSeen()
{
	APawn* AIPawn = GetPawn();
	FHitResult HitResult;

	if (LineOfSightTo(PlayerPawn) && IsPlayerInFront())
	{
		bool bObjectHit = GetWorld()->LineTraceSingleByChannel(HitResult, AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation()*1.1, ECollisionChannel::ECC_EngineTraceChannel2);

		if (!bObjectHit)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
		return false;
}

