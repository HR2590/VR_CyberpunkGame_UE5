

#include "ProyectoFinal/Public/Interactables/Door.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"
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

	
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::Interaction_Implementation()
{
	IInteractable::Interaction_Implementation();
	if (bIsOpened)
	{
		Close();
	}
	else
	{
		Open();
	}
}
