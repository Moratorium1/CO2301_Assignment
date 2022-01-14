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
			UE_LOG(LogTexture, Warning, TEXT("SpawnPoints"));
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
	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"));

	AThirdPersonController* PlayerController = Cast<AThirdPersonController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
		PlayerController->GameHasEnded(nullptr, false);

	EnemyNum--;
}

void AThirdPersonGameMode::Alarmed()
{
	UE_LOG(LogTexture, Warning, TEXT("Alarm Raised"));

	for (int i = 0; i <= SpawnPoints.Num() - 1; i++)
	{
		GetWorld()->SpawnActor<AThirdPersonCharacter>(EnemyClass, SpawnPoints[i]->GetActorLocation(), SpawnPoints[i]->GetActorRotation());
	}

	bPreviouslyAlarmed = true;
}

void AThirdPersonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((bAlarmed) && (!bPreviouslyAlarmed))
		Alarmed();

	if (EnemyNum <= 0)
	{
		AThirdPersonController* PlayerController = Cast<AThirdPersonController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController());
		if (PlayerController == nullptr) return;

		if (PlayerController != nullptr)
			PlayerController->GameHasEnded(nullptr, true);
	}
}

void AThirdPersonGameMode::EnemyCount()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, Enemies);

	EnemyNum = Enemies.Num();
}

void AThirdPersonGameMode::GameOver(bool PlayerWon)
{

}

