#pragma once
#include <TheLastKnight/Agents/AI/NPCAgentDecorator.h>
#include "CoreMinimal.h"

class AEventDispatcher;
class ANPCAIController;

class NPCAgentDebugDecorator : public NPCAgentDecorator
{
public:

	NPCAgentDebugDecorator(std::shared_ptr<NAI::Goap::IAgent> agent, ANPCAIController* controller, AEventDispatcher* eventDispatcher);
	~NPCAgentDebugDecorator() = default;

	void Update(float elapsedTime) override;

	private:
		void SendPredicatesData();

	private:
		AEventDispatcher* mEventDispatcher;
		ANPCAIController* mController;
};