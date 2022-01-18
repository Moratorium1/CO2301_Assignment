// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonController.h"
#include "Engine/TargetPoint.h"

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
	{
		if (Waypoints[i]->ActorHasTag(TEXT("SpawnPoint")))
		{
			SpawnPoints.Add(Waypoints[i]);
		}
	}
}

void AThirdPersonGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetSpawnPoints();
	EnemyCount();
}

void AThirdPersonGameMode::PawnKilled(APawn* PawnKilled)
{
	AThirdPersonController* PlayerController = Cast<AThirdPersonController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(PlayerController->GetPawn(), false);
		return;
	}

	EnemyNum--;

	if (EnemyNum <= 0)
	{	
		PlayerController = Cast<AThirdPersonController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetController());
		if (PlayerController == nullptr) return;

		PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
	}
}

void AThirdPersonGameMode::Alarmed()
{
	for (int i = 0; i <= SpawnPoints.Num() - 1; i++)
	{
		GetWorld()->SpawnActor<AThirdPersonCharacter>(EnemyClass, SpawnPoints[i]->GetActorLocation(), SpawnPoints[i]->GetActorRotation());
		EnemyNum++;
	}

	bPreviouslyAlarmed = true;
}

void AThirdPersonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((bAlarmed) && (!bPreviouslyAlarmed))
		Alarmed();
}

void AThirdPersonGameMode::EnemyCount()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, Enemies);

	EnemyNum = Enemies.Num();
}

