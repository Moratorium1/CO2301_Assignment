// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GameModeAlarmRaised.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonAIController.h"
#include "ThirdPersonGameMode.h"

UBTTask_GameModeAlarmRaised::UBTTask_GameModeAlarmRaised()
{
    NodeName = "Set GameMode Alarm True";
}

EBTNodeResult::Type UBTTask_GameModeAlarmRaised::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AThirdPersonGameMode* GameMode = Cast<AThirdPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    if (GameMode == nullptr)
        return EBTNodeResult::Failed;

    GameMode->bAlarmed = true;
    return EBTNodeResult::Succeeded;
}
