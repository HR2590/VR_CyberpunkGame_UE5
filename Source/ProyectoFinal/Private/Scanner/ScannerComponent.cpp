

#include "Scanner/ScannerComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Scanner/ScanneableComponent.h"


UScannerComponent::UScannerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UScannerComponent::BeginPlay()
{
	Super::BeginPlay();

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
	
}


void UScannerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UScannerComponent::StartEndScan()
{
	if (bEnabledSystem)
	{
		bEnabledSystem = false;
		
		//Disable color widget
	}
	else
	{
		bEnabledSystem = true;

		//Enable color widget
	}
}

void UScannerComponent::ScanItem()
{
	if (!Item) return;
	
	UScanneableComponent* Scanneable = Item->FindComponentByClass<UScanneableComponent>();
	if (Scanneable)
	{
		Scanneable->EnableScaneableUI();
	}
	
}

