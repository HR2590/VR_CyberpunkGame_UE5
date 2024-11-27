#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

#include "Equipables/Equippable.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRCore = CreateDefaultSubobject<USceneComponent>(TEXT("VR_Body"));
	RootComponent = VRCore;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VR_Camera"));
	VRCamera->SetupAttachment(RootComponent);

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
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &AVRPawn::HandleTeleport, DISTANCE_TELEPORT);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &AVRPawn::PickupObject, DISTANCE_GRAB);
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
		if (!ObjectGrabbed) 
		{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();

			if (HitComponent->IsSimulatingPhysics() && HitComponent->ComponentHasTag(PICKABLE_TAG))
			{
				HitComponent->AttachToComponent(L_MotionController, FAttachmentTransformRules::SnapToTargetIncludingScale);
				HitComponent->SetSimulatePhysics(false);

				CaughtComponent = HitComponent;

				ObjectGrabbed = true;
			}else if(HitComponent->IsSimulatingPhysics()==false && HitComponent->ComponentHasTag(EQUIPPABLE_TAG))
			{
				HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				HitComponent->AttachToComponent(L_MotionController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				HitComponent->SetSimulatePhysics(false);

				CaughtComponent = HitComponent;

				ObjectGrabbed = true;
			}
		}
		else
		{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();

			if (HitComponent && HitComponent->ComponentHasTag(EQUIPPABLE_TAG) && !ObjectEquipped)
			{
				EquippedMask = Cast<AEquippable>(HitComponent->GetOwner());

					HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			
					HitComponent->AttachToComponent(VRCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					HitComponent->SetSimulatePhysics(false);
					EquippedMask->EquipAction();

					ObjectEquipped = true;
					ObjectGrabbed = false;
				
			}else if (HitComponent)
			{
				HitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				HitComponent->SetSimulatePhysics(true);

				ObjectEquipped = false;
				ObjectGrabbed = false;
			}
		}
	}
}

void AVRPawn::HandleTeleport(float _distance)
{
	if (PlayerController) 
	{
		FVector Location;
		FRotator Rotation;

		PlayerController->GetPlayerViewPoint(Location, Rotation);
		FVector EndLocation = Location + (Rotation.Vector() * _distance);
		FHitResult HitResult;

		bool raycastHit = PerformRaycast(Location, EndLocation, HitResult);

		if (raycastHit) 
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, 10.f, 12, FColor::Red, false, 1000);
			FVector TeleportLocation = FVector(HitResult.Location.X, HitResult.Location.Y, this->GetActorLocation().Z);
			this->SetActorLocation(TeleportLocation);
		}
	}
}

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