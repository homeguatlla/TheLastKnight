#pragma once
#include <TheLastKnight/Agents/AI/NPCAgentDecorator.h>
#include "CoreMinimal.h"

class AEventDispatcher;

class NPCAgentDebugDecorator : public NPCAgentDecorator
{
public:

	NPCAgentDebugDecorator(std::shared_ptr<NAI::Goap::IAgent> agent, AEventDispatcher* eventDispatcher);
	~NPCAgentDebugDecorator() = default;

	void Update(float elapsedTime) override;

	private:
		AEventDispatcher* mEventDispatcher;
};