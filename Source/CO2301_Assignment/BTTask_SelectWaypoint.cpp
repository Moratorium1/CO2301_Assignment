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

    if (AIController == nullptr)
        return EBTNodeResult::Failed;

    int SelectedWayPoint = FMath::RandRange(0, AIController->Waypoints.Num() - 1);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AIController->Waypoints[SelectedWayPoint]->GetActorLocation());

    return EBTNodeResult::Type();
}
