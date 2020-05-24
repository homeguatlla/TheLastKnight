#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventDispatcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHealth, float, Health);

UCLASS(Blueprintable)
class AEventDispatcher : public AActor
{
	GENERATED_BODY()

	public:
		AEventDispatcher() = default;

		UPROPERTY(BlueprintAssignable, Category="Character")
		FUpdateHealth OnUpdateHealth;
};
