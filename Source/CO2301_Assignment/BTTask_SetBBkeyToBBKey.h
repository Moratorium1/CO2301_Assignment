// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBBkeyToBBKey.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API UBTTask_SetBBkeyToBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetBBkeyToBBKey();

protected:

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector BlackboardKeyA;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector BlackboardKeyB;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
