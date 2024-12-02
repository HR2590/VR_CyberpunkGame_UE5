#include "LaserGunActor.h"

ALaserGunActor::ALaserGunActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALaserGunActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> children;
	Children.Empty();
	RootComponent->GetChildrenComponents(true, children);

	for (USceneComponent* Child : children)
	{
		UAudioComponent* audioComponent = Cast<UAudioComponent>(Child);
		UNiagaraComponent* particleComponent = Cast<UNiagaraComponent>(Child);

		if (particleComponent) 
		{
			ShootEffect = particleComponent;
			ShootPivot = Child;
		}
	}
}

void ALaserGunActor::ShootWeapon(float _distance)
{
	FVector Location = ShootPivot->GetComponentLocation();

	FVector EndLocation = Location + (ShootPivot->GetForwardVector() * _distance);
	FHitResult HitResult;

	if (ShootEffect) 
		ShootEffect->Activate();

	FVector DestinationVectorAux;

	bool raycastHit = PerformRaycast(Location, EndLocation, HitResult);

	if (raycastHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		DestinationVectorAux = HitResult.Location;
	}
	else
		DestinationVectorAux = EndLocation;
	
	ShootEffect->SetVectorParameter(TEXT("BeamEnd"), DestinationVectorAux);
}

//that should be converted into a template
bool ALaserGunActor::PerformRaycast(FVector _location, FVector _endLocation, FHitResult& _hitResult)
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

