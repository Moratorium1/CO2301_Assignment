// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GameModeAlarmRaised.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API UBTTask_GameModeAlarmRaised : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UBTTask_GameModeAlarmRaised();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
