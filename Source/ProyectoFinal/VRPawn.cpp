#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <DrawerActor.h>

#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SplineComponent.h"
#include "Equipables/Equippable.h"
#include "StaticTeleportPlace.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRCore = CreateDefaultSubobject<USceneComponent>(TEXT("VR_Body"));
	RootComponent = VRCore;
	
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VR_Camera"));
	VRCamera->SetupAttachment(RootComponent);

		VRHeadCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HeadCollision"));
	VRHeadCollision->SetSphereRadius(25.0f);
	VRHeadCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	VRHeadCollision->SetupAttachment(VRCamera);

	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);
	L_MotionController->SetTrackingMotionSource(FName("Left"));

	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->SetupAttachment(RootComponent);
	R_MotionController->SetTrackingMotionSource(FName("Right"));

	AnchorPointLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Anchor_Point_Left"));
	AnchorPointLeft->SetupAttachment(L_MotionController);
	
	AnchorPointRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Anchor_Point_Right"));
	AnchorPointRight->SetupAttachment(R_MotionController);

	ParabolicEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParabolicEffect"));
	ParabolicEffect->SetupAttachment(RootComponent);

	TeleportEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportEffect"));
	TeleportEffect->SetupAttachment(RootComponent);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ObjectGrabbed && CaughtComponent)
	{
		FVector TargetLocation = L_MotionController->GetComponentLocation();
		FRotator TargetRotation = L_MotionController->GetComponentRotation();

		CaughtComponent->SetWorldLocationAndRotation(TargetLocation, TargetRotation);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &AVRPawn::PerformParabolicRaycast);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Completed, this, &AVRPawn::HandleTeleport);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &AVRPawn::PickupObject, DISTANCE_GRAB);
		EnhancedInputComponent->BindAction(RevealAction, ETriggerEvent::Triggered, this, &AVRPawn::RevealActionTrigger);
	}
}



void AVRPawn::PickupObject(float _distance)
{
	FVector Location = L_MotionController->GetComponentLocation();

	FVector EndLocation = Location + (L_MotionController->GetForwardVector() * _distance);
	FHitResult HitResult;

	bool raycastHit = PerformRaycast(Location, EndLocation, HitResult);

	if (raycastHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		if(!ObjectGrabbed && ObjectEquipped && HitComponent && HitComponent->ComponentHasTag(EQUIPPABLE_TAG))
		{
			UnEqquip(HitComponent);
		}	
		else if (!ObjectGrabbed && HitComponent)
		{
			HandleObjectPickup(HitComponent);
		}
		else if(ObjectGrabbed && HitComponent && HitComponent->ComponentHasTag(EQUIPPABLE_TAG))
		{
			CheckEquippableObjectIsOnFace(HitComponent);
		}
		else if (ObjectGrabbed && HitComponent)
		{
			ReleaseObject(HitComponent);
		}
		
		SetupRevealAction(HitResult.GetActor());
	
	}
}

void AVRPawn::HandleObjectPickup(UPrimitiveComponent* HitComponent)
{
	if (HitComponent->ComponentHasTag(PICKABLE_TAG))
	{
		PickupPhysicsObject(HitComponent);
	}
	else if (HitComponent->ComponentHasTag(DRAWER_TAG))
	{
		PickupDrawerObject(HitComponent);
	}
}

void AVRPawn::PickupPhysicsObject(UPrimitiveComponent* HitComponent)
{
	CaughtComponent = HitComponent;
	if (HitComponent->IsSimulatingPhysics())
	{
		HitComponent->AttachToComponent(L_MotionController, FAttachmentTransformRules::SnapToTargetIncludingScale);
		HitComponent->SetSimulatePhysics(false);
		ObjectGrabbed = true;
	}
}


void AVRPawn::PickupDrawerObject(UPrimitiveComponent* HitComponent)
{
	AActor* OwnerActor = HitComponent->GetOwner();

	if (OwnerActor && OwnerActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		IInteractable::Execute_InteractionHit(OwnerActor, HitComponent);
}

void AVRPawn::CheckEquippableObjectIsOnFace(UPrimitiveComponent* HitComponent)
{
	Equippable = Cast<AEquippable>(HitComponent->GetOwner());
	
	if(VRHeadCollision->IsOverlappingActor(Equippable) && HitComponent && HitComponent->ComponentHasTag(EQUIPPABLE_TAG) && !ObjectEquipped)
	{
		HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			
		HitComponent->AttachToComponent(VRCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		HitComponent->SetSimulatePhysics(false);
		Equippable->EquipAction();

		ObjectEquipped = true;
		ObjectGrabbed = false;
	}
	else
	{
		ReleaseObject(HitComponent);
	}
}

void AVRPawn::UnEqquip(UPrimitiveComponent* HitComponent)
{
	Equippable = Cast<AEquippable>(HitComponent->GetOwner());
	HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	HitComponent->AttachToComponent(L_MotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Equippable->UnEquipAction();
	ObjectEquipped = false;
	ObjectGrabbed = true;
}

void AVRPawn::ReleaseObject(UPrimitiveComponent* HitComponent)
{
	if (ObjectGrabbed && HitComponent)
	{
		HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		HitComponent->SetSimulatePhysics(true);
		ObjectGrabbed = false;
	}
}

//that should be converted into a template
bool AVRPawn::PerformRaycast(FVector _location, FVector _endLocation, FHitResult& _hitResult)
{
	FCollisionQueryParams TraceParams;
	TraceParams.bTraceComplex = false;
	TraceParams.AddIgnoredActor(this);

	bool raycastHit = GetWorld()->LineTraceSingleByChannel(
		_hitResult,
		_location,
		_endLocation,
		ECC_Visibility,
		TraceParams
	);

	return raycastHit;
}

void AVRPawn::RevealActionTrigger()
{
}

void AVRPawn::SetupRevealAction(AActor* InActor)
{
	if (!InActor) return;
	if(InActor->ActorHasTag("RevealGun"))RevealAction_ImplementableEvent(InActor);
}


void AVRPawn::PerformParabolicRaycast()
{
	if (!bTeleport)
	{
		ToggleFixedPointsVisibility(true);
	}
	
	//Prepare all the varables for the projectile path
	FPredictProjectilePathParams PathParams;
	PathParams.StartLocation = R_MotionController->GetComponentLocation();
	PathParams.LaunchVelocity = R_MotionController->GetForwardVector() * ParabolicVelocity;
	PathParams.bTraceWithCollision = true;
	PathParams.ProjectileRadius = ProjectileRadius;
	PathParams.MaxSimTime = MaxSimTime;
	PathParams.SimFrequency = SimFrequency;
	PathParams.OverrideGravityZ = OverrideGravityZ;
	PathParams.TraceChannel = ECC_GameTraceChannel2;
	PathParams.DrawDebugType = bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;
	PathParams.ActorsToIgnore.Add(this);
	

	FPredictProjectilePathResult PathResult;
	bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), PathParams, PathResult);

	// If hit succesfull, we set the varable to teleport location
	if (bHit)
	{
		AActor* HitActor = PathResult.HitResult.GetActor();
		if (HitActor->Tags.Contains("Wall"))
		{
			bTeleport=false;
			TeleportLocation=FVector(0.0f);
			ParabolicEffect->DeactivateImmediate();
			TeleportEffect->DeactivateImmediate();
			
			return;
		}
			
		if (HitActor && HitActor->IsA<AStaticTeleportPlace>())
		{
			// Obtener el FixedPointActor
			AStaticTeleportPlace* FixedActor = Cast<AStaticTeleportPlace>(HitActor);

			// Ajustar el punto de teleportación al centro del FixedPointActor
			TeleportLocation = FixedActor->GetStaticPoint();

			// Centrar el efecto de teleportación en el punto fijo
			TeleportEffect->SetWorldLocation(TeleportLocation);

			// Activar el efecto de teleportación con el centro ajustado
			TeleportEffect->Activate();
		}
		else
		{
			TeleportEffect->SetWorldLocation(PathResult.HitResult.ImpactPoint);
			TeleportEffect->Activate();
			TeleportLocation = PathResult.HitResult.ImpactPoint;
		}
		
		ParabolicEffect->Activate();
		ParabolicEffect->SetVectorParameter(FName("Start"), PathParams.StartLocation);
		ParabolicEffect->SetVectorParameter(FName("End"), PathResult.HitResult.ImpactPoint);

		
		bTeleport = true;
	}

}

void AVRPawn::HandleTeleport()
{
	// if we can teleport we teleport to the location
	if (bTeleport)
	{
		TeleportLocation.Z = GetActorLocation().Z;
		SetActorLocation(TeleportLocation);
		bTeleport = false;
		ToggleFixedPointsVisibility(false);
		ParabolicEffect->DeactivateImmediate();
		TeleportEffect->DeactivateImmediate();
	}
}

void AVRPawn::ToggleFixedPointsVisibility(bool bVisible)
{

	TArray<AActor*> FixedPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticTeleportPlace::StaticClass(), FixedPoints);
	
	for (AActor* Actor : FixedPoints)
	{
		AStaticTeleportPlace* FixedPoint = Cast<AStaticTeleportPlace>(Actor);
		if (FixedPoint)
		{
			if (bVisible)
			{
				FixedPoint->ShowFixedPoint();
			}
			else
			{
				FixedPoint->HideFixedPoint();
			}
		}
	}
}