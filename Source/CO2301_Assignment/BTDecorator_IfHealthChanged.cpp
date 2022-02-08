// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IfHealthChanged.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTDecorator_IfHealthChanged::UBTDecorator_IfHealthChanged()
{
	NodeName = "If Health Changed?";
}

void UBTDecorator_IfHealthChanged::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	EBlackboardCompare::Type CompareResult = OwnerComp.GetBlackboardComponent()->CompareKeyValues(UBlackboardKeyType::StaticClass(), BlackboardKey3.GetSelectedKeyID(), BlackboardKey2.GetSelectedKeyID());
}