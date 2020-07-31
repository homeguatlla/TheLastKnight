#pragma once
#include <TheLastKnight/NAI/source/goap/agent/AgentContext.h>
#include <TheLastKnight/NAI/source/utils/fsm/BaseState.h>
#include <TheLastKnight/NAI/source/goap/GoapTypes.h>
#include <vector>

namespace NAI
{
	namespace Goap
	{
		class IAction;

		class Processing : public core::utils::FSM::BaseState<AgentState, AgentContext>
		{
		public:
			Processing() = default;
			virtual ~Processing() = default;
			AgentState GetID() const override { return AgentState::STATE_PROCESSING; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;
			void OnExit(float deltaTime) override;
			
			void OnPredicatesListChanged();

		private:
			std::shared_ptr<IAction> GetNextActionToProcess();
			bool ThereAreActionsToProcess() const;
			void Accomplished();
			void Abort();
			void AddActionPostConditionsToPredicatesList(std::shared_ptr<IAction> action);

		private:
			std::shared_ptr<IAction> mCurrentAction;
			std::vector<std::shared_ptr<IPredicate>> mPredicates;
		};
	}
}
