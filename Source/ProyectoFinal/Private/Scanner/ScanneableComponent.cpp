

#include "Scanner/ScanneableComponent.h"


UScanneableComponent::UScanneableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UScanneableComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UScanneableComponent::EnableScaneableUI()
{
	//Enable
}

void UScanneableComponent::DisableScaneableUI()
{
	//Disable
}


void UScanneableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

