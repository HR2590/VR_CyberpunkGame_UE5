
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactables/Interactable.h"
#include "BaseDestructable.generated.h"

class UProceduralMeshComponent;

UCLASS()
class PROYECTOFINAL_API ABaseDestructable : public AActor
{
	GENERATED_BODY()

public:
	ABaseDestructable();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseDestructable")
	UProceduralMeshComponent* ProceduralMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;
	
public:
	

	
};
