#include "NPCAgentDebugDecorator.h"
#include <TheLastKnight/EventDispatcher.h>

NPCAgentDebugDecorator::NPCAgentDebugDecorator(
std::shared_ptr<NAI::Goap::IAgent> agent, 
AEventDispatcher* eventDispatcher) :
NPCAgentDecorator(agent),
mEventDispatcher(eventDispatcher)
{

}

void NPCAgentDebugDecorator::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);
	mEventDispatcher->OnLogPredicate.Broadcast("Predicado");
}