#pragma once
#include "IAgent.h"
#include <vector>
#include <memory>

namespace core
{
	namespace utils
	{
		namespace FSM
		{
			class StatesMachine;
		}
	}
}

namespace NAI
{
	namespace Goap
	{
		class IGoal;

		class BaseAgent : public IAgent
		{
		public:
			BaseAgent(std::shared_ptr<IGoapPlanner> goapPlanner,
				std::vector<std::shared_ptr<IGoal>>& goals,
				std::vector<std::shared_ptr<IPredicate>>& predicates);
			virtual ~BaseAgent() = default;

			AgentState GetCurrentState() const override;
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

