// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "ThirdPersonCharacter.h"

UBTService_UpdateHealth::UBTService_UpdateHealth()
{
	NodeName = "Update Health";
}

void UBTService_UpdateHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AThirdPersonCharacter* Character = Cast<AThirdPersonCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
		return;

	if (OwnerComp.GetAIOwner() == nullptr)
		return;

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), Character->Health);
}