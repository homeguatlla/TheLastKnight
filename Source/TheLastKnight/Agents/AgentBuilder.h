#pragma once
#include <vector>
#include <memory>
#include <TheLastKnight/Agents/AI/NPCAgentDebugDecorator.h>

class IAgentAIController;
class AEventDispatcher;
class ANPCAIController;

namespace NAI {
	namespace Goap {
		class IGoapPlanner;
		class IGoal;
		class IPredicate;
		class IAgent;
	}
}

class NPCAgentDecorator;

class AgentBuilder
{
public:
	AgentBuilder() = default;
	AgentBuilder& AddGoapPlanner(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner);
	AgentBuilder& AddGoal(std::shared_ptr<NAI::Goap::IGoal> goal);
	AgentBuilder& AddPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate);
	AgentBuilder& AddController(ANPCAIController* controller);
	AgentBuilder& AddEventDispatcher(AEventDispatcher* eventDispatcher);

	template<class TAgent>
	std::shared_ptr<NAI::Goap::IAgent> Build()
	{
		auto agent = std::make_shared<TAgent>(mGoapPlanner, mGoals, mPredicates, mController);
		auto debugAgent = std::make_shared<NPCAgentDebugDecorator>(agent, mController, mEventDispatcher);

		return debugAgent;
	}
	
private:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	std::shared_ptr<NAI::Goap::IGoapPlanner> mGoapPlanner;
	std::vector<std::shared_ptr<NAI::Goap::IGoal>> mGoals;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> mPredicates;
	ANPCAIController* mController;
	AEventDispatcher* mEventDispatcher;
};
