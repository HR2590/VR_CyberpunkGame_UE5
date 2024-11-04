
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PROYECTOFINAL_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;

	bool bUpIsOpen = false;
	bool bDownIsOpen = false;
	bool bIsOpening = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector UpTargetLocation = FVector(0, 0, 200);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float UpMoveSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector DownTargetLocation = FVector(0, 0, -50);;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DownMoveSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* UpMovableMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* DownMovableMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Door")
	UBoxComponent* KeyInteractBoxVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* OpenSoundEffect;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AActor* ActorDoorKey;

private:
	UFUNCTION()
	void OpenUpMesh(float DeltaTime);
	void OpenDownMesh(float DeltaTime);
	
};
