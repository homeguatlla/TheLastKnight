#pragma once
#include <TheLastKnight/NAI/source/goap/agent/IAgent.h>


class NPCAgentDecorator : public NAI::Goap::IAgent
{
public:

	NPCAgentDecorator(std::shared_ptr<NAI::Goap::IAgent> agent);
	~NPCAgentDecorator() = default;

	void Update(float elapsedTime) override;
	glm::vec3 GetPosition() const override;
	void MoveTo(float elapsedTime, const glm::vec3& point) override;

private:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
};