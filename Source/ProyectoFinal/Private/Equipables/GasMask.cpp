// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipables/GasMask.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGasMask::AGasMask()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create proximity component
	ProximitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProximitySphere"));
	ProximitySphere->InitSphereRadius(10.0f);
	RootComponent = ProximitySphere;

	//ProximitySphere->OnComponentHit.AddDynamic(this, &AGasMask::HandleHit);

	bIsEquipped = false;
}

// Called when the game starts or when spawned
void AGasMask::BeginPlay()
{
	Super::BeginPlay();

}

// void AGasMask::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
// 						 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// {
// 	// Si colisiona con el jugador y no está attach a nada
// 	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
// 	if (PlayerController && OtherActor == PlayerController->GetPawn() && 
// 		RootComponent && RootComponent->GetAttachParent() == nullptr)
// 	{
// 		CheckEquipCondition();
// 	}
// }

void AGasMask::CheckEquipCondition()
{
	if (bIsEquipped) return;

	// Get the player camera location
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		// Check distance to the camera
		if (FVector::Dist(GetActorLocation(), CameraLocation) <= 20.0f) // Adjust radius as needed
		{
			EquipMask();
		}
	}
}

void AGasMask::EquipMask()
{
	// Asegurarse de que solo se equipe una vez
	if (bIsEquipped) return;

	bIsEquipped = true;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			// Obtener la cámara del jugador
			UCameraComponent* PlayerCamera = PlayerPawn->FindComponentByClass<UCameraComponent>();
			if (PlayerCamera)
			{
				if (IsAttachedTo(nullptr))
				{
					// El actor está attach a algo
					// Attachear la máscara a la cámara del jugador
					AttachToComponent(PlayerCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					// Ajustar posición y rotación relativa usando RootComponent
					if (RootComponent)
					{
						RootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));  // Ajusta la posición
						RootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // Ajusta la rotación
					}
				}
			}
		}
	}
}



