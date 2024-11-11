// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawerActor.h"

// Sets default values
ADrawerActor::ADrawerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrawerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ClampPosition(const FVector& _position, const FVector& _minPosition, const FVector& _maxPosition)
{
    return FVector(
        FMath::Clamp(_position.X, _minPosition.X, _maxPosition.X),
        FMath::Clamp(_position.Y, _minPosition.Y, _maxPosition.Y),
        FMath::Clamp(_position.Z, _minPosition.Z, _maxPosition.Z)
    );
}

void ADrawerActor::SetDrawerBoundaries(FVector _start, FVector _end) 
{

    TArray<UPrimitiveComponent*> parentComponents;
    this->GetComponents<UPrimitiveComponent>(parentComponents);

    for (UPrimitiveComponent* parentComponent : parentComponents)
    {
        if (parentComponent)
        {
            TArray<USceneComponent*> attachedChildren = parentComponent->GetAttachChildren();

            for (USceneComponent* childComponent : attachedChildren)
            {
                if (UPrimitiveComponent* primitiveChild = Cast<UPrimitiveComponent>(childComponent))
                {
                    FVector clampedVector = ClampPosition(primitiveChild->GetRelativeLocation(), _start, _end);
                    /*UE_LOG(LogTemp, Warning, TEXT("Clamped Vector: X=%f, Y=%f, Z=%f"), clampedVector.X, clampedVector.Y, clampedVector.Z);*/

                    primitiveChild->SetRelativeLocation(clampedVector);
                }
            }
        }
    }
}

// Called every frame
void ADrawerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    SetDrawerBoundaries(FVector(0, 0, 0), FVector(0, 30, 0));
}

