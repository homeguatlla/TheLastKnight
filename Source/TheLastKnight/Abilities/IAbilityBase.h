#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/IAbility.h>
#include <TheLastKnight/Abilities/AbilitityBase.h>

#include "IAbilityBase.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UAbilityBase : public UInterface
{
	GENERATED_BODY()
};

class IAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "AbilityBase")
	virtual void DoCast(const FVector& location) = 0;
};