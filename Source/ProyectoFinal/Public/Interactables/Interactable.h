
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class PROYECTOFINAL_API IInteractable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void Interaction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractionHit(UPrimitiveComponent* HitComponent);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void PawnInteraction(APawn* Pawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void KatanaInteraction(FVector ImpactLocation, FVector PointNormal);
	
};
