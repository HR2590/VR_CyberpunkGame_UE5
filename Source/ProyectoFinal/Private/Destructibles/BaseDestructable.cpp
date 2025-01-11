

#include "Destructibles/BaseDestructable.h"
#include "ProceduralMeshComponent.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"

ABaseDestructable::ABaseDestructable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetVisibility(false);
	StaticMesh->SetHiddenInGame(true);
	StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(RootComponent);

	ProceduralMeshComponent->SetSimulatePhysics(true);
	ProceduralMeshComponent->bUseComplexAsSimpleCollision = false;
	
	ProceduralMeshComponent->SetCollisionProfileName(TEXT("Custom"));
	ProceduralMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	ProceduralMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ProceduralMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	
}

void ABaseDestructable::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseDestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

