

#include "Scanner/ScannerComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KismetTraceUtils.h"
#include "PropertyAccess.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Scanner/ScanneableComponent.h"
#include "Serialization/CompactBinary.h"
#include "KismetTraceUtils.h"


UScannerComponent::UScannerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UScannerComponent::BeginPlay()
{
	Super::BeginPlay();

	//Starts inputs
	APlayerController* PlayerController = Cast<APlayerController>(Cast<AVRPawn>(GetOwner())->GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMCScannerContext, 1);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		EnhancedInputComponent->BindAction(StartEndScanAction, ETriggerEvent::Started, this, &UScannerComponent::StartEndScan);
		EnhancedInputComponent->BindAction(ScanAction, ETriggerEvent::Started, this, &UScannerComponent::ScanItem);
	}
	//End inputs

	//We get the CameraController We will use it to know where is the player looking in the tick
	OwnerActorCameraComponent = Cast<AVRPawn>(GetOwner())->GetComponentByClass<UCameraComponent>();

	//We create the timer for the scanner to perform the cast
	GetWorld()->GetTimerManager().SetTimer(ScanTimerHandle, this, &UScannerComponent::Scan, ScanFrequency, true);
	GetWorld()->GetTimerManager().PauseTimer(ScanTimerHandle);
	
}

void UScannerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
// const FString FormattedStringPosition = FString::Printf(TEXT("Position: %s"), *OwnerActorCameraComponent->GetComponentLocation().ToString());
// const FString FormattedStringRotation = FString::Printf(TEXT("Rotation: %s"), *OwnerActorCameraComponent->GetComponentRotation().ToString());
//
// GEngine->AddOnScreenDebugMessage(1, -1, FColor::Yellow, FormattedStringPosition);
// GEngine->AddOnScreenDebugMessage(2, -1, FColor::Red, FormattedStringRotation);

}

void UScannerComponent::StartEndScan()
{
	if (bEnabledSystem)
	{
		bEnabledSystem = false;
		DeactivateScanner();
		GetWorld()->GetTimerManager().PauseTimer(ScanTimerHandle);
	}
	else
	{
		bEnabledSystem = true;
		ActivateScanner();
		GetWorld()->GetTimerManager().UnPauseTimer(ScanTimerHandle);
	}
}

void UScannerComponent::ScanItem()
{
	float LastDistance = 0.0f;
	Item = nullptr;
	
	for (const auto& Hit : OutHits)
	{
		if (Hit.GetActor()->GetComponentByClass<UScanneableComponent>())
		{
			float Distance = FVector::Distance(Hit.ImpactPoint, OwnerActorCameraComponent->GetComponentLocation());
			if (Distance > LastDistance)
			{
				Item = Hit.GetActor();
				LastDistance = Distance;
			}
		}
	}

	if (Item)
	{
		InfoToUI(Item->GetComponentByClass<UScanneableComponent>());
	}
	else
	{
		InfoToUI(nullptr);
	}
	
}

void UScannerComponent::Scan()
{
	if (!bEnabledSystem) return;

	FVector CurrentLocation = OwnerActorCameraComponent->GetComponentLocation();
	const FRotator CurrentRotation = OwnerActorCameraComponent->GetComponentRotation();
	const FVector CurrentForwardVector = CurrentRotation.Vector();
	const FVector CurrentEndLocation = CurrentLocation + CurrentForwardVector * ScanDistance;

	CurrentLocation = CurrentLocation + CurrentForwardVector * 50;

	TArray<AActor*> ActorsToIgnore;
	//We dont want to sweep the owner of the component
	ActorsToIgnore.Add(GetOwner());
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);
	Params.bTraceComplex = false;
	Params.TraceTag = FName(TEXT("SphereTraceMulti"));
	
	bool BHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		CurrentLocation,
		CurrentEndLocation,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(ScanScope),
		Params
	);


#if WITH_EDITOR
	DrawDebugSphereTraceMulti(GetWorld(),
		CurrentLocation,
		CurrentEndLocation,
		ScanScope,
		EDrawDebugTrace::ForDuration,
		BHit, OutHits,
		FColor::Green,
		FColor::Red,
		ScanFrequency);
#endif
	
	
	/*bool BHit = UKismetSystemLibrary::SphereTraceMulti(this,
		CurrentLocation, CurrentEndLocation,
		ScanScope,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		ActorsToIgnore,
		bScanDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		OutHits,
		true,
		FLinearColor::Green,
		FLinearColor::Blue,
		ScanFrequency);*/

}

