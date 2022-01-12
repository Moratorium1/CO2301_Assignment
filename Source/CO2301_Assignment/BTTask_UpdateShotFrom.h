// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UpdateShotFrom.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API UBTTask_UpdateShotFrom : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_UpdateShotFrom();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
