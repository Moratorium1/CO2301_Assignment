// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomWaypointInRadius.h"
#include "ThirdPersonCharacter.h"
#include "ThirdPersonAIController.h"
#include "NavigationSystem.h"

UBTTask_RandomWaypointInRadius::UBTTask_RandomWaypointInRadius()
{
    NodeName = "Select Random Waypoint";
}

EBTNodeResult::Type UBTTask_RandomWaypointInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
        return EBTNodeResult::Failed;

    AThirdPersonCharacter* Character = Cast<AThirdPersonCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    FNavLocation RandomPoint;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

    bool bLocationFound = NavSys->GetRandomReachablePointInRadius(Character->GetActorLocation(), Radius, RandomPoint);

    if (bLocationFound)
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomPoint.Location);

    return EBTNodeResult::Type();
}