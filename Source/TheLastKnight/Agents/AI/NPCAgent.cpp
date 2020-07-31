#include "NPCAgent.h"


NPCAgent::NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
	std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) : NAI::Goap::BaseAgent(goapPlanner, goals, predicates)
{

}

void NPCAgent::Update(float elapsedTime)
{
	BaseAgent::Update(elapsedTime);
}

glm::vec3 NPCAgent::GetPosition() const
{
	return glm::vec3(0.0f);
}

void NPCAgent::MoveTo(float elapsedTime, const glm::vec3& point)
{

}
