

#include "Destructibles/BaseDestructable.h"
#include "ProceduralMeshComponent.h"

ABaseDestructable::ABaseDestructable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetVisibility(false);
	StaticMesh->SetHiddenInGame(true);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(RootComponent);
	
}

void ABaseDestructable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseDestructable::KatanaInteraction_Implementation(FVector ImpactLocation, FVector PointNormal)
{
	IInteractable::KatanaInteraction_Implementation(ImpactLocation, PointNormal);
	CutObject(ImpactLocation, PointNormal);
}

void ABaseDestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

