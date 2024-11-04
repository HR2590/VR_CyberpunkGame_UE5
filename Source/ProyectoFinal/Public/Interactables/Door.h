
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EDoorType : uint8
{
	RDT_Slide UMETA(DisplayName = "Slide"),
	RDT_RotateRight UMETA(DisplayName = "Slide"),
	RDT_RotateLeft UMETA(DisplayName = "Slide")
};

UCLASS()
class PROYECTOFINAL_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;

	bool bIsOpen = false;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* MovableMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Door")
	UBoxComponent* KeyInteractBoxVolume;

	UPROPERTY(EditAnywhere, Category = "Door")
	TSubclassOf<AActor> EnabledClass;

	UPROPERTY(EditAnywhere)
	EDoorType DoorType = EDoorType::RDT_Slide;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OpenDoor();
};
