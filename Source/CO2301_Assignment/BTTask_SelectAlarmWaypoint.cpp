// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectAlarmWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonAIController.h"
#include "ThirdPersonGameMode.h"

UBTTask_SelectAlarmWaypoint::UBTTask_SelectAlarmWaypoint()
{
	NodeName = "Select Alarm Waypoint";
}

EBTNodeResult::Type UBTTask_SelectAlarmWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get AI controller cast to AThirdPersonController in order to access Waypoints Array
	AThirdPersonAIController* AIController = Cast<AThirdPersonAIController>(OwnerComp.GetAIOwner());

	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AThirdPersonGameMode* GameMode = Cast<AThirdPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode == nullptr)
		return EBTNodeResult::Failed;

	if (GameMode->bAlarmed)
		return EBTNodeResult::Failed;

	// Loop through array searching for way point with the Alarm tag
	for (int i = 0; i < AIController->PatrolPoints.Num() - 1; i++)
	{
		if (AIController->PatrolPoints[i]->ActorHasTag(TEXT("Alarm")))
		{	// Update the blackboard key selected with the object for the alarm waypoint
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), AIController->PatrolPoints[i]);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
