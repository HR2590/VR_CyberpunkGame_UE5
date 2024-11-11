// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawerActor.generated.h"

UCLASS()
class PROYECTOFINAL_API ADrawerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetDrawerBoundaries(FVector _start, FVector _end);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
