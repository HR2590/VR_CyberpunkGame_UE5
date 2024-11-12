// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawerActor.h"

// Sets default values
ADrawerActor::ADrawerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrawerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrawerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DrawerCaught)
	{
		FVector lerpPosition = FMath::VInterpTo(DrawerCaught->GetRelativeLocation(), DrawerMovementVector, DeltaTime, LERP_SPEED);
		DrawerCaught->SetRelativeLocation(lerpPosition);
	}
}

void ADrawerActor::CallDrawerAction(UPrimitiveComponent* HitComponent)
{
	DrawerCaught = HitComponent;
	FVector localPosition = DrawerCaught->GetRelativeLocation();
	DrawerMovementVector = FVector(0, 0, 0);

	AActor* OwnerActor = DrawerCaught->GetOwner();

	if (OwnerActor && OwnerActor->IsA<ADrawerActor>())
	{
		float minBoundary = ClosePosition;
		float maxBoundary = OpenPosition;

		if (FMath::IsNearlyEqual(localPosition.Y, minBoundary))
			DrawerMovementVector.Y = maxBoundary;
		else if (FMath::IsNearlyEqual(localPosition.Y, maxBoundary))
			DrawerMovementVector.Y = minBoundary;
	}
}

