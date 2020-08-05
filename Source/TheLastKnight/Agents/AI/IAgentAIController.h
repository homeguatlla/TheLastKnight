
#pragma once
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
	UFUNCTION()
	virtual FVector GetPosition() const = 0;
	virtual void MoveTo(float elapsedTime, const FVector& point) = 0;
};