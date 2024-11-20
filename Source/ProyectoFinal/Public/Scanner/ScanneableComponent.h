
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "ScanneableComponent.generated.h"


class UScannerComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROYECTOFINAL_API UScanneableComponent : public UWidgetComponent
{
	GENERATED_BODY()

	friend UScannerComponent;

public:
	UScanneableComponent();

protected:
	virtual void BeginPlay() override;

	FText Text;

	void EnableScaneableUI();
	void DisableScaneableUI();
	

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
