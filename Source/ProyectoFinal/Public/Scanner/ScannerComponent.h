
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProyectoFinal/VRPawn.h"
#include "ScannerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROYECTOFINAL_API UScannerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScannerComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="ScannerInputs")
	UInputMappingContext* IMCScannerContext;

	UPROPERTY(EditAnywhere, Category="ScannerInputs")
	UInputAction* StartEndScanAction;

	UPROPERTY(EditAnywhere, Category="ScannerInputs")
	UInputAction* ScanAction;

	UPROPERTY(EditAnywhere, Category="ScannerInputs")

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, Category="Scanner")
	AActor* Item;

	TArray<UScanneableComponent*> ;

	UPROPERTY(EditAnywhere, Category="Scanner")
	bool bEnabledSystem = false;

	void StartEndScan();

	void ScanItem();

	
};
