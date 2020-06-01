#pragma once
#include "CoreMinimal.h"
#include "IAbilityBaseHUD.generated.h"

UINTERFACE(Blueprintable)
class UAbilityBaseHUD : public UInterface
{
	GENERATED_BODY()
};

class IAbilityBaseHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyStartCasting(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyCast(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyCooldownTime(const FString& name, float remainingTime);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyReadyToCast(const FString& name);
};