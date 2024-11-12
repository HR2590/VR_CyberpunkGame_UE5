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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer Settings")
	float ClosePosition = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawer Settings")
	float OpenPosition = 30.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CallDrawerAction(UPrimitiveComponent* HitComponent);

private:
	UPrimitiveComponent* DrawerCaught;
	FVector DrawerMovementVector;

	const float LERP_SPEED = 2.f;

};
