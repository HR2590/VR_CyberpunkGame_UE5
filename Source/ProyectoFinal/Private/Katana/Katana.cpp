

#include "Katana/Katana.h"

#include "Components/BoxComponent.h"


AKatana::AKatana()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(StaticMesh);

	StartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("StartLocation"));
	StartLocation->SetupAttachment(StaticMesh);
	
	EndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("EndLocation"));
	EndLocation->SetupAttachment(StaticMesh);
	
}

void AKatana::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKatana::PawnInteraction_Implementation(APawn* Pawn)
{
	IInteractable::PawnInteraction_Implementation(Pawn);
	
	
}



void AKatana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



