

#include "ProyectoFinal/Public/Interactables/Door.h"
#include "Components/BoxComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	MovableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovableMesh"));
	MovableMesh->SetupAttachment(RootComponent);

	KeyInteractBoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyInteractBoxVolume"));
	KeyInteractBoxVolume->SetupAttachment(MovableMesh);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	KeyInteractBoxVolume->OnComponentBeginOverlap.AddDynamic(this,&ADoor::OverlapBegin);

}

void ADoor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsOpen) return;
	OpenDoor();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::OpenDoor()
{
	if (DoorType == EDoorType::RDT_Slide)
	{
		MovableMesh->AddRelativeLocation(FVector(0,	100, 0));
		//TODO MOVIMIENTO UNIFORME
	}

	bIsOpen = true;
}

