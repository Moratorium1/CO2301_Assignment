// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "ThirdPersonAIController.h"

void AThirdPersonAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (AIBehavior != nullptr)
		RunBehaviorTree(AIBehavior);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
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

