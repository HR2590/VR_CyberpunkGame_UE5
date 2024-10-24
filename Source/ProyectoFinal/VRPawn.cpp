#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

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
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &AVRPawn::HandleTeleport);
	}
}

void AVRPawn::HandleTeleport()
{
	if (PlayerController) 
	{
		FVector Location;
		FRotator Rotation;

		PlayerController->GetPlayerViewPoint(Location, Rotation);
		FVector EndLocation = Location + (Rotation.Vector() * DISTANCE);

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		TraceParams.bTraceComplex = false;
		TraceParams.AddIgnoredActor(this);

		bool raycastHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Location,
			EndLocation,
			ECC_Visibility,
			TraceParams
		);

		if (raycastHit) 
		{
			DrawDebugSphere(GetWorld(), HitResult.Location, 10.f, 12, FColor::Red, false, 1000);
			FVector TeleportLocation = FVector(HitResult.Location.X, HitResult.Location.Y, this->GetActorLocation().Z);
			this->SetActorLocation(TeleportLocation);
		}
	}
}
