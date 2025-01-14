#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserReceptor.generated.h"

UCLASS(Blueprintable)
class PROYECTOFINAL_API ALaserReceptor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaserReceptor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "ReceptorInteract")
	void TurnOnLaserReceptor();

};
