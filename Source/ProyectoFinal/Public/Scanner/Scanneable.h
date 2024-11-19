
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Scanneable.generated.h"

UINTERFACE()
class UScanneable : public UInterface
{
	GENERATED_BODY()
};


class PROYECTOFINAL_API IScanneable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Scanner")
	void Scanning();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Scanner")
	void EndScanning();
	
};
