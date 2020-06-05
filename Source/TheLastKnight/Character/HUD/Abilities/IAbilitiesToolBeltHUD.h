#pragma once
#include <UObject/ScriptInterface.h>
#include "IAbilitiesToolBeltHUD.generated.h"

/**
 * Basic character HUD interface
 */
UINTERFACE(Blueprintable)
class UAbilitiesToolBeltHUD : public UInterface
{
	GENERATED_BODY()
};

class IAbilitiesToolBeltHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Tool Belt")
	void OnAddAbilityIntoToolBelt(const FString& name, UTexture2D* icon, int slot);
};