#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventDispatcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHealth, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddAbilityIntoToolBelt, UTexture2D*, icon, int, slot);

UCLASS(Blueprintable)
class AEventDispatcher : public AActor
{
	GENERATED_BODY()

	public:
		AEventDispatcher() = default;

		UPROPERTY(BlueprintAssignable, Category="Character Health")
		FUpdateHealth OnUpdateHealth;

		UPROPERTY(BlueprintAssignable, Category = "Character Ability")
		FAddAbilityIntoToolBelt OnAddAbilityIntoToolBelt;
};
