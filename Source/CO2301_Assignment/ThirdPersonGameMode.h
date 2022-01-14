// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonCharacter.h"
#include "ThirdPersonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API AThirdPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AThirdPersonGameMode();

	UPROPERTY(EditAnywhere)
	bool bAlarmed = false;

	UPROPERTY(EditAnywhere)
	bool bPreviouslyAlarmed = false;

	UFUNCTION()
	void EnemyCount();

	UPROPERTY(EditAnywhere)
	int EnemyNum;

	UFUNCTION()
	void PawnKilled(APawn* PawnKilled);

private:

	UFUNCTION()
	void Alarmed();

	UPROPERTY()
	TArray<AActor*> Waypoints;

	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	UFUNCTION()
	void GetSpawnPoints();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AThirdPersonCharacter> EnemyClass;

	UPROPERTY()
	TArray<AActor*> Enemies;

	UFUNCTION()
	void GameOver(bool PlayerWon);

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
