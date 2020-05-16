#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS(Blueprintable)
class AAbility : public AActor
{
	GENERATED_BODY()

	public:
		AAbility() = default;

		/*Ability is being cast*/
		UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void OnStartCasting(const FVector& location);

		/*Ability is being effective*/
		UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void OnCast();
};
