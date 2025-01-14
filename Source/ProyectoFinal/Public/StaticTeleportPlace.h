// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticTeleportPlace.generated.h"

UCLASS()
class PROYECTOFINAL_API AStaticTeleportPlace : public AActor
{
	GENERATED_BODY()

public:	
	AStaticTeleportPlace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticPoint")
	class UStaticMeshComponent* FixedMesh;

	// Helper function to get the center point
	UFUNCTION(BlueprintCallable, Category = "StaticPoint")
	FVector GetStaticPoint() const;

	UFUNCTION(BlueprintCallable, Category = "FixedPoint")
	void ShowFixedPoint();

	UFUNCTION(BlueprintCallable, Category = "FixedPoint")
	void HideFixedPoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FixedPoint")
	UStaticMeshComponent* TeleportIndicator;
};
