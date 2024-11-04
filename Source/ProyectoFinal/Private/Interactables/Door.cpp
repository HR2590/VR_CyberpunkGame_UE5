

#include "ProyectoFinal/Public/Interactables/Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent =	CreateDefaultSubobject<USceneComponent>("Root");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	UpMovableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovableMesh"));
	UpMovableMesh->SetupAttachment(StaticMesh);

	DownMovableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DownMovableMesh"));
	DownMovableMesh->SetupAttachment(StaticMesh);

	KeyInteractBoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyInteractBoxVolume"));
	KeyInteractBoxVolume->SetupAttachment(StaticMesh);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	KeyInteractBoxVolume->OnComponentBeginOverlap.AddDynamic(this,&ADoor::OverlapBegin);

}

void ADoor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (ActorDoorKey && OtherActor == ActorDoorKey && !bUpIsOpen && !bDownIsOpen)
	{
		bIsOpening = true;
		if (OpenSoundEffect) UGameplayStatics::PlaySoundAtLocation(this, OpenSoundEffect, GetActorLocation(), 0.3f);
	}
	
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpening)
	{
		if (!bDownIsOpen)
		{
			OpenDownMesh(DeltaTime);
		}

		if (!bUpIsOpen)
		{
			OpenUpMesh(DeltaTime);
		}
	}

	if (bDownIsOpen && bUpIsOpen)
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void ADoor::OpenUpMesh(float DeltaTime)
{
	FVector const CurrentLocation = UpMovableMesh->GetRelativeLocation();
	FVector const NewLocation = FMath::VInterpTo(CurrentLocation, UpTargetLocation, DeltaTime, UpMoveSpeed);
	UpMovableMesh->SetRelativeLocation(NewLocation);
	if (UpMovableMesh->GetRelativeLocation().Z > UpTargetLocation.Z)
	{
		bUpIsOpen = true;
	}
}

void ADoor::OpenDownMesh(float DeltaTime)
{
	FVector const CurrentLocation = DownMovableMesh->GetRelativeLocation();
	FVector const NewLocation = FMath::VInterpTo(CurrentLocation, DownTargetLocation, DeltaTime, DownMoveSpeed);
	DownMovableMesh->SetRelativeLocation(NewLocation);
	if (DownMovableMesh->GetRelativeLocation().Z < DownTargetLocation.Z)
	{
		bDownIsOpen = true;
	}
}
