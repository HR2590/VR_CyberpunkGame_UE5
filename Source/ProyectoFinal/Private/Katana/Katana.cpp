

#include "Katana/Katana.h"

#include "Components/BoxComponent.h"
#include "ProyectoFinal/VRPawn.h"


AKatana::AKatana()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxPickable = CreateDefaultSubobject<UBoxComponent>("BoxPickable");
	RootComponent = BoxPickable;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetupAttachment(RootComponent);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(StaticMesh);
	
	HitBox->SetCollisionProfileName(TEXT("Custom"));
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);
	
}

void AKatana::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKatana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



