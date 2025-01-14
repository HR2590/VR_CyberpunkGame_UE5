// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <EngineFwd.h>
#include <VREditorInteractor.h>
#include <UserSettings/EnhancedInputUserSettings.h>

#include "Components/SphereComponent.h"
#include "VRPawn.generated.h"

class UNiagaraComponent;
class USplineComponent;
class AEquippable;

UCLASS()
class PROYECTOFINAL_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;

	//BASE VR SET
	UPROPERTY()
	USceneComponent* VRCore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Set")
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Set")
	USphereComponent* VRHeadCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Controllers")
	UMotionControllerComponent* L_MotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Controllers")
	UMotionControllerComponent* R_MotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Controllers Mesh")
	UStaticMeshComponent* AnchorPointLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR Controllers Mesh")
	UStaticMeshComponent* AnchorPointRight;
	
	//BASE VR SET

	//INPUT SYSTEM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* TeleportAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RevealAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* GrabAction;
	//INPUT SYSTEM
	
	// PARABOLIC TELEPORT FUNCTIONS
	void HandleTeleport();
	void PerformParabolicRaycast();
	// PARABOLIC TELEPORT FUNCTIONS
    UPROPERTY()
	UPrimitiveComponent* CaughtComponent;

	// PARABOLIC TELEPORT VARIABLES
	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	float ParabolicVelocity = 1000.0f;
	
	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	float ProjectileRadius = 5.0f;
	
	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	float MaxSimTime = 3.0f;
	
	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	float SimFrequency = 15.0f;
	
	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	float OverrideGravityZ = -980.0f;

	UPROPERTY(EditAnywhere, Category = "ParabolicData")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, Category = "ParabolicVisuals")
	UNiagaraComponent* ParabolicEffect;

	UPROPERTY(EditAnywhere, Category = "ParabolicVisuals")
	UNiagaraComponent* TeleportEffect;
	// PARABOLIC TELEPORT VARIABLES

	//REVEAL GUN VARIABLES
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PickupObject(float _distance);

	void HandleObjectPickup(UPrimitiveComponent* HitComponent);

	void PickupPhysicsObject(UPrimitiveComponent* HitComponent);
	

	void PickupDrawerObject(UPrimitiveComponent* HitComponent);

	void CheckEquippableObjectIsOnFace(UPrimitiveComponent* HitComponent);

	void UnEqquip(UPrimitiveComponent* HitComponent);

	void ReleaseObject(UPrimitiveComponent* HitComponent);
	bool PerformRaycast(FVector _location, FVector _endLocation, FHitResult& HitResult);

//REVEAL GUN FUNCTIONS
	
	void RevealActionTrigger();
	UFUNCTION(BlueprintImplementableEvent)
	void RevealAction_ImplementableEvent(AActor* InActor);
	void SetupRevealAction(AActor* InActor);
	
	void ToggleFixedPointsVisibility(bool bVisible);

private:
	const float DISTANCE_TELEPORT = 1000;
	const float DISTANCE_GRAB = 1000;
	const FName PICKABLE_TAG = "Pickable";
	const FName EQUIPPABLE_TAG = "Equippable";
	const FName DRAWER_TAG = "Drawer";
	APlayerController* PlayerController;
	


	AEquippable* Equippable = nullptr;

	bool ObjectGrabbed;
	bool ObjectEquipped;

	FVector TeleportLocation;
	bool bTeleport = false;
};


