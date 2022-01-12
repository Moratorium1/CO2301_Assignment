// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectAlarmWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonAIController.h"

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

	// Loop through array searching for way point with the Alarm tag
	for (int i = 0; i < AIController->Waypoints.Num() - 1; i++)
	{
		if (AIController->Waypoints[i]->ActorHasTag(TEXT("Alarm")))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), AIController->Waypoints[i]);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
