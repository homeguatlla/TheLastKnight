#pragma once
#include <vector>
#include <memory>

class IAgentAIController;

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
	AgentBuilder& AddController(IAgentAIController* controller);

	template<class TAgent>
	std::shared_ptr<NAI::Goap::IAgent> Build()
	{
		auto agent = std::make_shared<TAgent>(mGoapPlanner, mGoals, mPredicates, mController);

#ifdef _DEBUG
		agent = std::make_shared<NPCAgentDecorator>(agent);
#endif

		return agent;
	}
	
private:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	std::shared_ptr<NAI::Goap::IGoapPlanner> mGoapPlanner;
	std::vector<std::shared_ptr<NAI::Goap::IGoal>> mGoals;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> mPredicates;
	IAgentAIController* mController;
};
