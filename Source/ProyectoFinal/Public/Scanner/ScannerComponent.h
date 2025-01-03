
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProyectoFinal/VRPawn.h"
#include "ScannerComponent.generated.h"

class UScanneableComponent;
struct FTimerHandle;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROYECTOFINAL_API UScannerComponent : public UWidgetComponent
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

	UPROPERTY(EditAnywhere, Category="Scanner")
	UUserWidget* ScannerOverlay;
	
	//Scan values
	UPROPERTY(EditAnywhere, Category="ScannerValues")
	float ScanDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category="ScannerValues")
	float ScanScope = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category="ScannerValues")
	float ScanFrequency = 0.25f;
	//Scan values

	UFUNCTION(BlueprintImplementableEvent, Category="Scanner")
	void InfoToUI(UScanneableComponent* ScanneableComponent);

	UFUNCTION(BlueprintImplementableEvent, Category="Scanner")
	void DeactivateScanner();

	UFUNCTION(BlueprintImplementableEvent, Category="Scanner")
	void ActivateScanner();

	UFUNCTION(BlueprintImplementableEvent, Category="Scanner")
	void UpdateUI();

	UPROPERTY(BlueprintReadOnly)
	TArray<FHitResult> OutHits;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	UCameraComponent* OwnerActorCameraComponent;

	UPROPERTY(EditAnywhere, Category="Scanner")
	AActor* Item;

	UPROPERTY(EditAnywhere, Category="Scanner")
	bool bEnabledSystem = false;

	UPROPERTY()
	FTimerHandle ScanTimerHandle;

	UFUNCTION()
	virtual void StartEndScan();

	UFUNCTION()
	virtual void ScanItem();

	UFUNCTION()
	virtual void Scan();

	
};
