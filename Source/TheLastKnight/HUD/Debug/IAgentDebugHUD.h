#pragma once
#include "CoreMinimal.h"
#include "IAgentDebugHUD.generated.h"

UINTERFACE(Blueprintable)
class UAgentDebugHUD : public UInterface
{
	GENERATED_BODY()
};

class IAgentDebugHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnLogPredicate(const FString& text);
};