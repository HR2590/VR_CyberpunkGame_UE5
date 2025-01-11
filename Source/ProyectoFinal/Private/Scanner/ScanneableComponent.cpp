

#include "Scanner/ScanneableComponent.h"


UScanneableComponent::UScanneableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UScanneableComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UScanneableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

