#include "AgentBuilder.h"

AgentBuilder& AgentBuilder::AddGoapPlanner(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner)
{
	mGoapPlanner = goapPlanner;
	return *this;
}

AgentBuilder& AgentBuilder::AddGoal(std::shared_ptr<NAI::Goap::IGoal> goal)
{
	mGoals.push_back(goal);
	return *this;
}

AgentBuilder& AgentBuilder::AddPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	mPredicates.push_back(predicate);
	return *this;
}

AgentBuilder& AgentBuilder::AddController(IAgentAIController* controller)
{
	mController = controller;
	return *this;
}

AgentBuilder& AgentBuilder::AddEventDispatcher(AEventDispatcher* eventDispatcher)
{
	mEventDispatcher = eventDispatcher;
	return *this;
}
