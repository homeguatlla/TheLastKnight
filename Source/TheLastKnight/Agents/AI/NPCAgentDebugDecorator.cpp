#include "NPCAgentDebugDecorator.h"
#include <TheLastKnight/EventDispatcher.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>

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

	mEventDispatcher->OnLogClear.Broadcast();

	const auto predicates = mAgent->GetPredicates();

	for(auto&& predicate : predicates)
	{
		mEventDispatcher->OnLogPredicate.Broadcast(UTF8_TO_TCHAR(predicate->GetFullText().c_str()));
	}
}