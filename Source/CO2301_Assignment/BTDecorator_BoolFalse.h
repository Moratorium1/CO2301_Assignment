// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_BoolFalse.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API UBTDecorator_BoolFalse : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_BoolFalse();

protected:
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;

};
