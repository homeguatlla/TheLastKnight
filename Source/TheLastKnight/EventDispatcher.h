#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventDispatcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHealth, float, health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAddAbilityIntoToolBelt, const FString&, abilityName, UTexture2D*, icon, int, slot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyStartCasting, const FString&, abilityName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyCast, const FString&, abilityName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNotifyCooldownTime, const FString&, abilityName, float, remainingTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyReadyToCast, const FString&, abilityName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLogPredicate, const FString&, text);


UCLASS(Blueprintable)
class AEventDispatcher : public AActor
{
	GENERATED_BODY()

	public:
		AEventDispatcher() = default;

		UPROPERTY(BlueprintAssignable, Category="Character Health")
		FUpdateHealth OnUpdateHealth;

		UPROPERTY(BlueprintAssignable, Category = "Character Tool Belt")
		FAddAbilityIntoToolBelt OnAddAbilityIntoToolBelt;

		UPROPERTY(BlueprintAssignable, Category = "Character Ability")
		FNotifyStartCasting OnNotifyStartCasting;
		UPROPERTY(BlueprintAssignable, Category = "Character Ability")
		FNotifyCast OnNotifyCast;
		UPROPERTY(BlueprintAssignable, Category = "Character Ability")
		FNotifyCooldownTime OnNotifyCooldownTime;
		UPROPERTY(BlueprintAssignable, Category = "Character Ability")
		FNotifyReadyToCast OnNotifyReadyToCast;

		UPROPERTY(BlueprintAssignable, Category="Agent Log")
		FLogPredicate OnLogPredicate;
};
