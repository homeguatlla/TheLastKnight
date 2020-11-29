#include "NPCAgentDebugDecorator.h"
#include <TheLastKnight/EventDispatcher.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>

NPCAgentDebugDecorator::NPCAgentDebugDecorator(
std::shared_ptr<NAI::Goap::IAgent> agent, 
ANPCAIController* controller,
AEventDispatcher* eventDispatcher) :
NPCAgentDecorator(agent),
mEventDispatcher(eventDispatcher),
mController(controller)

{

}

void NPCAgentDebugDecorator::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);

	if(IsEnbled())
	{ 
		SendPredicatesData();
	}
}

void NPCAgentDebugDecorator::SendPredicatesData()
{
	mEventDispatcher->OnLogClear.Broadcast();
	const auto predicates = mAgent->GetPredicates();

	for (auto&& predicate : predicates)
	{
		mEventDispatcher->OnLogPredicate.Broadcast(
			mController,
			UTF8_TO_TCHAR(predicate->GetFullText().c_str()));
	}
}