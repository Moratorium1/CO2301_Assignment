// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UpdateShotFrom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTTask_UpdateShotFrom::UBTTask_UpdateShotFrom()
{
	NodeName = "Set Shot From";
}

EBTNodeResult::Type UBTTask_UpdateShotFrom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
		return EBTNodeResult::Failed;

	if (OwnerComp.GetAIOwner() == nullptr)
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());

	return EBTNodeResult::Succeeded;
}