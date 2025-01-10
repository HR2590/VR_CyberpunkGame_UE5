
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "ScanneableComponent.generated.h"


class UScannerComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROYECTOFINAL_API UScanneableComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UScannerComponent;

public:
	UScanneableComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DescriptionText;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
