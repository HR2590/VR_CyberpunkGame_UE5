
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VolumeKeyInteractor.generated.h"

class UBoxComponent;

/*
 * This actor, works as a trigger for a other actor @InteractableActor if this actor implements the interface IInteractable
 * When a designated actor @ActorDoorKey begin overlaps the box component @KeyInteractBoxVolume
 * 
 */

UCLASS()
class PROYECTOFINAL_API AVolumeKeyInteractor : public AActor
{
	GENERATED_BODY()

public:
	AVolumeKeyInteractor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Volume")
	UBoxComponent* KeyInteractBoxVolume;

	UPROPERTY(EditInstanceOnly, Category = "Key")
	AActor* ActorDoorKey;

	UPROPERTY(EditInstanceOnly, Category = "Key")
	AActor* InteractableAActor;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public:
	virtual void Tick(float DeltaTime) override;
};
