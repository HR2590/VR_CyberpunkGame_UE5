// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GasMask.generated.h"

class USphereComponent;

UCLASS()
class PROYECTOFINAL_API AGasMask : public AActor
{
	GENERATED_BODY()

public:
	AGasMask();

protected:
	virtual void BeginPlay() override;
	

private:

	//UFUNCTION()
	//void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//			   FVector NormalImpulse, const FHitResult& Hit);

	void CheckEquipCondition();
	void EquipMask();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ProximitySphere;
	

	bool bIsEquipped;
};
