#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPHealthAbility.generated.h"

UCLASS(Blueprintable)
class ABPHealthAbility : public AActor
{
	GENERATED_BODY()

	public:
		ABPHealthAbility() = default;

		/*Ability is being cast*/
		UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void OnCast(const FVector& location);
};
