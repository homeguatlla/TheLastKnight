#include "NPCAgentDebugDecorator.h"
#include <TheLastKnight/EventDispatcher.h>
#include <NAI/include/goap/IPredicate.h>
#include <TheLastKnight/utils/UtilsLibrary.h>
#include <algorithm>

const float NEW_PREDICATE_TIME = 5.0f;
const float	REMOVING_PREDICATE_TIME = 3.0f;

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
	
	if(IsEnabled())
	{
		auto predicates = mAgent->GetPredicates();
		UpdateAndRemovePredicatesList(predicates);
		AddNewPredicates(predicates);
		UpdatePredicateStates(elapsedTime);
		//TODO improvement: we can only send data when data has changed. The problem is that
		//we need to know a npc change to mark data as dirty. We cannot receive the nextNPC, previousNPC events
		//due this is not a unreal class. 
		SendPredicatesData();
	}
}
void NPCAgentDebugDecorator::UpdateAndRemovePredicatesList(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	for(auto&& predicate : mPredicates)
	{
		auto it = std::find_if(
			predicates.begin(),
			predicates.end(), 
			[predicate](const std::shared_ptr<NAI::Goap::IPredicate> element)
			{
				return predicate.text.compare(element->GetFullText()) == 0;
			});
		
		const bool found = it != predicates.end();
		if(found)
		{
			if(predicate.type == PredicateStateType::REMOVING)
			{
				predicate.type = PredicateStateType::NORMAL;
				predicate.timer = 0.0f;
			}
			predicates.erase(it);
		}
		else if(predicate.type != PredicateStateType::REMOVING)
		{
			predicate.type = PredicateStateType::REMOVING;
			predicate.timer = REMOVING_PREDICATE_TIME;
		}
	}
}

void NPCAgentDebugDecorator::AddNewPredicates(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	for(const auto predicate : predicates)
	{
		mPredicates.push_back(Predicate{predicate->GetFullText(), PredicateStateType::NEW, NEW_PREDICATE_TIME });
	}
}

void NPCAgentDebugDecorator::SendPredicatesData() const
{
	mEventDispatcher->OnLogClear.Broadcast(mController);
	
	for (auto&& predicate : mPredicates)
	{
		mEventDispatcher->OnLogPredicate.Broadcast(
			mController,
			static_cast<int>(predicate.type),
			utils::UtilsLibrary::ConvertToFString(predicate.text));
	}
}

void NPCAgentDebugDecorator::UpdatePredicateStates(float elapsedTime)
{
	for (auto it = mPredicates.begin(); it < mPredicates.end();)
	{
		switch(it->type)
		{
			case PredicateStateType::NEW:
				it->timer -= elapsedTime;
				if(it->timer <= 0)
				{
					it->timer = 0.0f;
					it->type = PredicateStateType::NORMAL;
				}
				++it;
			break;
			case PredicateStateType::REMOVING:
				it->timer -= elapsedTime;
				if (it->timer <= 0)
				{
					it = mPredicates.erase(it);
				}
				else
				{
					++it;
				}
			break;
			default:
				++it;
			break;
		}
	}
}
