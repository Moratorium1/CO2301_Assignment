// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

private:

	UFUNCTION()
		void Alarmed();

protected:
	virtual void Tick(float DeltaTime) override;
};
