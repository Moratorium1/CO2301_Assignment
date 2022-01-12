// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateHealth.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API UBTService_UpdateHealth : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateHealth();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
