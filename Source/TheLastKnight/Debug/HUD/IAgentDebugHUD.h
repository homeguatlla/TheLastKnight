#pragma once
#include "CoreMinimal.h"
#include "IAgentDebugHUD.generated.h"

UINTERFACE(Blueprintable)
class UAgentDebugHUD : public UInterface
{
	GENERATED_BODY()
};

class ANPCAIController;

class IAgentDebugHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnLogPredicate(const ANPCAIController* controller, const FString& text);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnLogClear();
};