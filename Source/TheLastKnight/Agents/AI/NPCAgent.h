#pragma once
#include <NAI/include/goap/agent/BaseAgent.h>
#include <NAI/include/goap/IGoapPlanner.h>
#include "CoreMinimal.h"

class IAgentAIController;

class NPCAgent : public NAI::Goap::BaseAgent
{
public:

	NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
		std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
		std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates, 
		IAgentAIController* controller);
	~NPCAgent() = default;

	void Update(float elapsedTime) override;
	glm::vec3 GetPosition() const override;
	void MoveTo(float elapsedTime, const glm::vec3& point) override;
	IAgentAIController* GetController() const { return mController; }

private:
	IAgentAIController* mController;
};