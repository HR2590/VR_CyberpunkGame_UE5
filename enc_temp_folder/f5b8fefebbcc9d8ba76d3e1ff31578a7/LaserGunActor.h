// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include <EnhancedInputLibrary.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ShootAction;

public:	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();
	void ShootWeapon(float _distance);
	void ActivateRayEffect(UNiagaraComponent* _particleSystem, float _deactivateDelay);

private:
	bool PerformRaycast(FVector _location, FVector _endLocation, FHitResult& _hitResult);

	const float PARTICLES_TIMER = 10.f;
};
