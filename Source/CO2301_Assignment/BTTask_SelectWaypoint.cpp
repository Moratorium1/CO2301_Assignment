// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectWaypoint.h"
#include "ThirdPersonAIController.h"
#include "Math/UnrealMathUtility.h"

UBTTask_SelectWaypoint::UBTTask_SelectWaypoint()
{
    NodeName = "Select Random Waypoint";
}

EBTNodeResult::Type UBTTask_SelectWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AThirdPersonAIController* AIController = Cast<AThirdPersonAIController>(OwnerComp.GetAIOwner());
    if (AIController == nullptr) return EBTNodeResult::Failed;

    // Select a random value between 0 and the total number of waypoints
    int SelectedPatrolPoints = FMath::RandRange(0, AIController->PatrolPoints.Num() - 1);

    // Pass the location of the randomly selected waypoint to the blackboard key
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AIController->PatrolPoints[SelectedPatrolPoints]->GetActorLocation());

    return EBTNodeResult::Type();
}
