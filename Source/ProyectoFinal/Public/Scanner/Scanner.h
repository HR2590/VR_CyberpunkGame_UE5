
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Scanner.generated.h"

class AVRPawn;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROYECTOFINAL_API UScanner : public UActorComponent
{
	GENERATED_BODY()

public:
	UScanner();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputScanner")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputScanner")
	UInputAction* ScanInputAction;
	
	virtual void BeginPlay() override;
	void Scan();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScannerParameters")
	float ScanDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScannerParameters")
	float ScanRadius;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY()
	AVRPawn* OwnerPawn;
	
};
