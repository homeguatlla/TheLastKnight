
#pragma once
#include "UObject/Interface.h"
#include "IAgentAIController.generated.h"

UINTERFACE()
class THELASTKNIGHT_API UAgentAIController : public UInterface
{
	GENERATED_BODY()
};

class IAgentAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Agent Controller")
	FString GetAgentName() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Agent Controller")
	FString GetAgentCurrentState() const;

	virtual FVector GetPosition() const = 0;
	virtual void MoveTo(float elapsedTime, const FVector& point) = 0;
};