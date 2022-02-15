// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "ThirdPersonCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThirdPersonGun.h"

// Sets default values
APickUp::APickUp()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionSphere->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
}

void APickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//If the OtherActor is not a character return
	AThirdPersonCharacter* CharacterOverlapped = Cast<AThirdPersonCharacter>(OtherActor);
	if (!CharacterOverlapped) return;

	// Give Overlapping Character Ammo or health
	if (HealAmount > 0)
		UGameplayStatics::ApplyDamage(OtherActor, -HealAmount, OtherActor->GetInstigatorController(), this, UDamageType::StaticClass());
	else
		CharacterOverlapped->ActiveWeapon->Resupply();
	
	Destroy();
}


