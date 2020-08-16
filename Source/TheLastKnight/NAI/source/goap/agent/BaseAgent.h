#pragma once
#include "IAgent.h"
#include "AgentContext.h"
#include <TheLastKnight/NAI/source/goap/GoapTypes.h>
#include <TheLastKnight/NAI/source/utils/fsm/StatesMachine.h>
#include <TheLastKnight/NAI/source/goap/agent/fsm/states/Planning.h>
#include <TheLastKnight/NAI/source/goap/agent/fsm/states/Processing.h>
#include <TheLastKnight/NAI/source/goap/agent/fsm/transitions/EnterPlanning.h>
#include <TheLastKnight/NAI/source/goap/agent/fsm/transitions/EnterProcessing.h>
#include <vector>
#include <memory>


namespace NAI
{
	namespace Goap
	{
		class IGoal;

		class BaseAgent : public IAgent, public std::enable_shared_from_this<BaseAgent>
		{
		public:
			BaseAgent(	std::shared_ptr<IGoapPlanner> goapPlanner, 
						std::vector<std::shared_ptr<IGoal>>& goals, 
						std::vector<std::shared_ptr<IPredicate>>& predicates);
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
			void StartUp() override;
			void Update(float elapsedTime) override;
			bool HasPredicate(int predicateID) const override;
			std::string WhereIam() const override;
			void OnNewPredicate(std::shared_ptr<IPredicate> predicate) override;
			std::vector<std::shared_ptr<IGoal>> GetGoals() const override { return mGoals; }

		private:
			void CreateStatesMachine();
			void NotifyPredicatesListChangedToProcessState();

		private:
			std::unique_ptr<core::utils::FSM::StatesMachine<AgentState, AgentContext>> mStatesMachine;
			std::shared_ptr<AgentContext> mAgentContext;
			std::shared_ptr<IGoapPlanner> mGoapPlanner;
			std::vector<std::shared_ptr<IPredicate>> mPredicates;
			std::vector<std::shared_ptr<IGoal>> mGoals;
		};
	}
}

