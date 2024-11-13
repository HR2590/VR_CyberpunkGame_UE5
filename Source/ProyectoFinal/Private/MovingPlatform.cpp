// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "DSP/Delay.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	bStop = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//Usar Timer
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
				DeltaDelay = DeltaTime;
				//bStop = true;
				
			}
			//UE_LOG(LogTemp, Warning, TEXT("Delta Time: %f, DeltaDelay %f, DeltaDelay + Delay %f"), DeltaTime, DeltaDelay, DeltaDelay + (Delay/1000));
			
			if (DeltaDelay + (Delay/1000) == DeltaTime)
			{
				bStop = false;
			}
			if(!bStop)
			{
				FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
				Location += Speed * DeltaTime * Direction;
				SetActorLocation(Location);
			}
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

