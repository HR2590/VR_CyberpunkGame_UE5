// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LaserGunActor.generated.h"

UCLASS()
class PROYECTOFINAL_API ALaserGunActor : public AActor
{
	GENERATED_BODY()

	USceneComponent* ShootPivot;
	
public:	
	ALaserGunActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShootEffect")
	UNiagaraComponent* ShootEffect;

public:	
	virtual void BeginPlay() override;
	void ShootWeapon(float _distance);

private:
	bool PerformRaycast(FVector _location, FVector _endLocation, FHitResult& _hitResult);
};
