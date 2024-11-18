

#include "Interactables/VolumeKeyInteractor.h"
#include "Components/BoxComponent.h"
#include "Interactables/Interactable.h"

AVolumeKeyInteractor::AVolumeKeyInteractor()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyInteractBoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyInteractBoxVolume"));
	RootComponent = KeyInteractBoxVolume;
}

void AVolumeKeyInteractor::BeginPlay()
{
	Super::BeginPlay();
	KeyInteractBoxVolume->OnComponentBeginOverlap.AddDynamic(this,&AVolumeKeyInteractor::OverlapBegin);
}

void AVolumeKeyInteractor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ActorDoorKey && InteractableAActor && OtherActor == ActorDoorKey)
	{
		if (InteractableAActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_Interaction(InteractableAActor);
		}
	}
}

void AVolumeKeyInteractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

