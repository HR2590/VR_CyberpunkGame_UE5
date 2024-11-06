
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

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

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DeltaTimeHandler = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float UpMoveSpeed = 210.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float DownMoveSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* UpMovableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DownMovableMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* OpenSoundEffect;

	UFUNCTION(BlueprintImplementableEvent)
	void Open();

	UFUNCTION(BlueprintImplementableEvent)
	void Close();
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction_Implementation() override;

private:
	
};
