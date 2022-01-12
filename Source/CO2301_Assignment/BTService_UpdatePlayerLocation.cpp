// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "ThirdPersonAIController.h"


UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = "Update Player Object if Seen";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
		return;

	if (OwnerComp.GetAIOwner() == nullptr)
		return;

		if (Cast<AThirdPersonAIController>(OwnerComp.GetAIOwner())->PlayerSeen())
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
		else
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

}
