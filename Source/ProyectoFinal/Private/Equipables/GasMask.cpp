// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipables/GasMask.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGasMask::AGasMask()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create proximity component
	ProximitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProximitySphere"));
	ProximitySphere->InitSphereRadius(5.0f);
	RootComponent = ProximitySphere;

	bIsEquipped = false;
}

// Called when the game starts or when spawned
void AGasMask::BeginPlay()
{
	Super::BeginPlay();
    
	// Bind to the OnActorBeginOverlap event
	OnActorBeginOverlap.AddDynamic(this, &AGasMask::HandleOverlap);
}


// Event handler for actor overlap
void AGasMask::HandleOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if the overlapping actor is the player
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController && OtherActor == PlayerController->GetPawn())
	{
		EquipMask();
	}
}

void AGasMask::EquipMask()
{
	if (bIsEquipped) return;

	bIsEquipped = true;

	//AQUI PONER LO QUE HACE LA MÁSCARA
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{

			UCameraComponent* PlayerCamera = PlayerPawn->FindComponentByClass<UCameraComponent>();
			if (PlayerCamera)
			{
				AttachToComponent(PlayerCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				
			}
		}
	}
}


