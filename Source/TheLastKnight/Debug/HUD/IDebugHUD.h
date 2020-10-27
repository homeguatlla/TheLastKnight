#pragma once
#include "CoreMinimal.h"
#include "IDebugHUD.generated.h"

UINTERFACE(Blueprintable)
class UDebugHUD : public UInterface
{
	GENERATED_BODY()
};

class IDebugHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Debug Mode")
	void OnEnableDebugMode(bool enable);
};