#include "NPCAgentDecorator.h"


NPCAgentDecorator::NPCAgentDecorator(std::shared_ptr<NAI::Goap::IAgent> agent) : mAgent{ agent }
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