#pragma once
#include <TheLastKnight/NAI/source/goap/agent/BaseAgent.h>

class NPCAgent : public NAI::Goap::BaseAgent
{
public:

	NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
		std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
		std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates);
	~NPCAgent() = default;

	void Update(float elapsedTime) override;
	glm::vec3 GetPosition() const override;
	void MoveTo(float elapsedTime, const glm::vec3& point) override;
};