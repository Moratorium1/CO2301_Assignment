// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLastKnown.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_UpdatePlayerLastKnown::UBTService_UpdatePlayerLastKnown()
{
	NodeName = "Update Player Last Known Location";
}

void UBTService_UpdatePlayerLastKnown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
		return;

	if (OwnerComp.GetAIOwner() == nullptr)
		return;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}