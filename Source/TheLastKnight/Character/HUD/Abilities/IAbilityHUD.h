#pragma once
#include <UObject/ScriptInterface.h>
#include "IAbilityHUD.generated.h"

/**
 * Basic character HUD interface
 */
UINTERFACE(Blueprintable)
class UAbilityHUD : public UInterface
{
	GENERATED_BODY()
};

class IAbilityHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnInitialize(UTexture2D* icon);
};