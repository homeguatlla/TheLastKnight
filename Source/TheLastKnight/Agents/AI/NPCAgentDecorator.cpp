#include "NPCAgentDecorator.h"


NPCAgentDecorator::NPCAgentDecorator(std::shared_ptr<NAI::Goap::IAgent> agent) : 
mAgent{ agent },
mIsEnabled {true}
{
}

void NPCAgentDecorator::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);
}

glm::vec3 NPCAgentDecorator::GetPosition() const
{
	return mAgent->GetPosition();
}

void NPCAgentDecorator::MoveTo(float elapsedTime, const glm::vec3& point)
{
	mAgent->MoveTo(elapsedTime, point);
}

void NPCAgentDecorator::StartUp()
{
	mAgent->StartUp();
}

NAI::Goap::AgentState NPCAgentDecorator::GetCurrentState() const
{
	return mAgent->GetCurrentState();
}

bool NPCAgentDecorator::HasPredicate(int predicateID) const
{
	return mAgent->HasPredicate(predicateID);
}

std::string NPCAgentDecorator::WhereIam() const
{
	return mAgent->WhereIam();
}

void NPCAgentDecorator::OnNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	mAgent->OnNewPredicate(predicate);
}

std::vector<std::shared_ptr<NAI::Goap::IGoal>> NPCAgentDecorator::GetGoals() const
{
	return mAgent->GetGoals();
}

std::vector<std::shared_ptr<NAI::Goap::IPredicate>> NPCAgentDecorator::GetPredicates() const
{
	return mAgent->GetPredicates();
}
