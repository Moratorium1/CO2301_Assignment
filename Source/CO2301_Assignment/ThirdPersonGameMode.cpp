// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonController.h"
#include "Engine/TargetPoint.h"
#include "EngineUtils.h"
#include "ThirdPersonAIController.h"

AThirdPersonGameMode::AThirdPersonGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AThirdPersonGameMode::GetSpawnPoints()
{
	// Fill the Waypoints array with all target points
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	// Loop through the Waypoints array and filter out any targetpoint with the SpawnPoint Tag
	for (int i = 0; i <= Waypoints.Num() - 1; i++)
		if (Waypoints[i]->ActorHasTag(TEXT("SpawnPoint")))
			SpawnPoints.Add(Waypoints[i]);
}

void AThirdPersonGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetSpawnPoints();
}

void AThirdPersonGameMode::Alarmed()
{	//Called via the tick function if bAlarmed is true and bPreviouslyAlarmed is false - this is the first time an AI has got to the GameModeAlarmRaised in there BT

	//Loop through all spawn points spawning new enemy characters
	for (int i = 0; i <= SpawnPoints.Num() - 1; i++)
		GetWorld()->SpawnActor<AThirdPersonCharacter>(EnemyClass, SpawnPoints[i]->GetActorLocation(), SpawnPoints[i]->GetActorRotation());

	//Set bPreviouslyAlarmed to true to prevent this method being called every tick
	bPreviouslyAlarmed = true;
}

void AThirdPersonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((bAlarmed) && (!bPreviouslyAlarmed))
		Alarmed();
}

void AThirdPersonGameMode::PawnKilled(APawn* PawnKilled)
{	//Function called from Character Take Damage if the Character died

	//Check if the PawnKilled is the player character by attempting to cast its controller to the controller 
	//If PlayerController != nullptr than the cast succeeded and the PawnKilled was the player EndGame is called with bPlayerIsWinner set to false
	AThirdPersonController* PlayerController = Cast<AThirdPersonController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
		EndGame(false);

	//Loop through all AI controllers in the world and check if any haven't died in which case return the game has not ended
	for (AThirdPersonAIController* Controller : TActorRange<AThirdPersonAIController>(GetWorld()))
		if (!Controller->HasDied())
			return;

	//If every AI controller is dead than EndGame is called with bPlayerIsWinner set to true
	EndGame(true);
}

void AThirdPersonGameMode::EndGame(bool bIsPlayerWinner)
{	//Called from PawnKilled if the player has died or all enemies

	//Loop through all controllers calling their GameHasEnded function
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		//bIsWinner is true if the both Controller is the players controller and bIsPlayerWinner was passed in as true
		//else it returns false, that is if the controller is not the players or bIsPlayerWinner was passed in as false
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

