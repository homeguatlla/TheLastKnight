#pragma once
#include <TheLastKnight/Agents/AI/NPCAgentDecorator.h>
#include "CoreMinimal.h"
#include <string>
#include <vector>

class AEventDispatcher;
class ANPCAIController;

enum class PredicateStateType
{
	NORMAL = 0,
	NEW = 1,
	REMOVING = 2
};

struct Predicate
{
	Predicate(const std::string& text, PredicateStateType type, float timer = 0.0f) :
		text {text}, type {type}, timer {timer} {}
	
	std::string text;
	PredicateStateType type;
	float timer;
};

class NPCAgentDebugDecorator : public NPCAgentDecorator
{
public:

	NPCAgentDebugDecorator(std::shared_ptr<NAI::Goap::IAgent> agent, ANPCAIController* controller, AEventDispatcher* eventDispatcher);
	~NPCAgentDebugDecorator() = default;

	void Update(float elapsedTime) override;

private:
		void UpdateAndRemovePredicatesList(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates);
		void AddNewPredicates(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates);
		void SendPredicatesData() const;
		void UpdatePredicateStates(float elapsedTime);
	
private:
		AEventDispatcher* mEventDispatcher;
		ANPCAIController* mController;
		std::vector<Predicate> mPredicates;
};