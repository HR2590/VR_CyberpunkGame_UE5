#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Equippable.generated.h"

UCLASS()
class PROYECTOFINAL_API AEquippable : public AActor
{
	GENERATED_BODY()

public:
	AEquippable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ProximitySphere;

	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void EquipAction();

	UFUNCTION(BlueprintImplementableEvent)
	void UnEquipAction();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MaskMesh;

	UPROPERTY(EditAnywhere)
	bool bIsEquipped;

};