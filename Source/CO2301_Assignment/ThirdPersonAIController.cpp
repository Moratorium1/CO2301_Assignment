// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "ThirdPersonAIController.h"

AActor* AThirdPersonAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

//void AThirdPersonAIController::RandomPatrol()
//	AActor* ChoosenWaypoint = ChooseWaypoint();
//	SetFocus(ChoosenWaypoint);
//	MoveToActor(ChoosenWaypoint);
//}

void AThirdPersonAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (AIBehavior != nullptr)
		RunBehaviorTree(AIBehavior);

	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

	/* 
		All levels should have an alarm, 2 lookouts, and 4 patrol points
		The for loop below fills in the enemy AI blackboard with the locations of these points
	*/
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
}

void AThirdPersonAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
	if (PlayerSeen())
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerPosition"), PlayerPawn->GetActorLocation());
	}
	else
		GetBlackboardComponent()->ClearValue(TEXT("PlayerPosition"));
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

void AThirdPersonAIController::GetWaypoints()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	for (AActor* Waypoint : Waypoints)
	{
		if (Waypoint->ActorHasTag(TEXT("Alarm")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("AlarmPosition"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("Lookout1")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("Lookout1Position"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("Lookout2")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("Lookout2Position"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("PatrolPoint1")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint1Position"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("PatrolPoint2")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint2Position"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("PatrolPoint3")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint3Position"), Waypoint->GetActorLocation());
		}

		if (Waypoint->ActorHasTag(TEXT("PatrolPoint4")))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint4Position"), Waypoint->GetActorLocation());
		}
	}
}

void AThirdPersonAIController::OnMoveCompleted(FAIRequestID RequestID, const
	FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//RandomPatrol();
}
