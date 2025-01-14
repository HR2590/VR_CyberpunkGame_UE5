// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticTeleportPlace.h"
#include "StaticTeleportPlace.h"


AStaticTeleportPlace::AStaticTeleportPlace()
{
	PrimaryActorTick.bCanEverTick = true;

	FixedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FixedMesh"));
	RootComponent = FixedMesh;

	TeleportIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportIndicator"));
	TeleportIndicator->SetupAttachment(FixedMesh);
	TeleportIndicator->SetVisibility(false);
}

// Called when the game starts or when spawned
void AStaticTeleportPlace::BeginPlay()
{
	Super::BeginPlay();
	FixedMesh->SetVisibility(false, true);
}

// Called every frame
void AStaticTeleportPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AStaticTeleportPlace::GetStaticPoint() const
{
	return GetActorLocation();
}

void AStaticTeleportPlace::ShowFixedPoint()
{
	if (FixedMesh)
	{
		FixedMesh->SetVisibility(true, true);
	}
}

void AStaticTeleportPlace::HideFixedPoint()
{
	if (FixedMesh)
	{
		FixedMesh->SetVisibility(false, true);
	}
}
