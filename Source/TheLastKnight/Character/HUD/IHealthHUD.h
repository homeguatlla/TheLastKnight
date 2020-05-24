#pragma once
#include <UObject/ScriptInterface.h>
#include "IHealthHUD.generated.h"

/**
 * Basic character HUD interface
 */
UINTERFACE(Blueprintable)
class UHealthHUD : public UInterface
{
	GENERATED_BODY()
};

class IHealthHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnUpdateHealth(float health);
};