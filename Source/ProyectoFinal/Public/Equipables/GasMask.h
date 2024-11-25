#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GasMask.generated.h"

UCLASS()
class PROYECTOFINAL_API AGasMask : public AActor
{
	GENERATED_BODY()

public:
	AGasMask();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ProximitySphere;

	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void EquipAction();
	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MaskMesh;

	UPROPERTY(EditAnywhere)
	bool bIsEquipped;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PlayerFace; // Referencia al componente del jugador

};