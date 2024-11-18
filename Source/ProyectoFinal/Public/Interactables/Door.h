
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

/**
 *
 *	This class is a Door that implements IInteractable and the method
 *	Interaction_Implementation opens and close the door
 *
 *
 ***/

UCLASS()
class PROYECTOFINAL_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsOpened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsOpeningOrClosing = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DeltaTimeHandler = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float UpZDistance = 210.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float DownZDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* UpMovableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DownMovableMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* OpenSoundEffect;

	/*The movment its handled in the blueprint*/
	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	/*The movment its handled in the blueprint*/
	UFUNCTION(BlueprintImplementableEvent)
	void Close();
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction_Implementation() override;

private:
	
};
