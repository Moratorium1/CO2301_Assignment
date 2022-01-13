// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetBBkeyToBBKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SetBBkeyToBBKey::UBTTask_SetBBkeyToBBKey()
{
	NodeName = "Set Key A to Key B";
}

EBTNodeResult::Type UBTTask_SetBBkeyToBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	BlackBoardComp->SetValueAsFloat(BlackboardKeyA.SelectedKeyName, BlackboardKeyB.GetSelectedKeyID());

	return EBTNodeResult::Succeeded;
}
