// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonGameMode.h"

AThirdPersonGameMode::AThirdPersonGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AThirdPersonGameMode::Alarmed()
{
	UE_LOG(LogTexture, Warning, TEXT("Alarm Raised"));
}

void AThirdPersonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAlarmed)
		Alarmed();
}
