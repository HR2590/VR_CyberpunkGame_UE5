
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables/Interactable.h"
#include "Katana.generated.h"

class UBoxComponent;

UCLASS()
class PROYECTOFINAL_API AKatana : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AKatana();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* HitBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* StartLocation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* EndLocation;

	virtual void PawnInteraction_Implementation(APawn* Pawn) override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
