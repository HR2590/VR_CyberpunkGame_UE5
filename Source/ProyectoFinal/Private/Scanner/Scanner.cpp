

#include "Scanner/Scanner.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProyectoFinal/VRPawn.h"


UScanner::UScanner()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UScanner::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<AVRPawn>(GetOwner());

	if (APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 1);
			
		}
	}

	if (UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(OwnerPawn->InputComponent))
	{
		InputComponent->BindAction(ScanInputAction, ETriggerEvent::Triggered, this, &UScanner::Scan);
	}
	
}

void UScanner::Scan()
{
	FVector BeginLocation = OwnerPawn->GetCameraComponent()->GetComponentLocation();
	FVector EndLocation = BeginLocation + OwnerPawn->GetCameraComponent()->GetForwardVector() * ScanDistance;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerPawn);
	TArray<FHitResult> Hits;
	
	UKismetSystemLibrary::SphereTraceMultiByProfile(OwnerPawn,
		BeginLocation,
		EndLocation,
		ScanRadius,
		FName(""),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		Hits,
		true);
	
	
}

void UScanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

