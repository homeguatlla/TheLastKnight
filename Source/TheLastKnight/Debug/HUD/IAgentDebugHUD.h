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
	void OnEnableDebugMode(bool enable);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnLogPredicate(const ANPCAIController* controller, int type, const FString& text);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnLogClear(const ANPCAIController* controller);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnNextNPC(const ANPCAIController* controller);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Agent Log")
	void OnPreviousNPC(const ANPCAIController* controller);
};