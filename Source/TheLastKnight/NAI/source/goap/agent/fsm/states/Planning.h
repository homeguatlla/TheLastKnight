#pragma once
#include <TheLastKnight/NAI/source/goap/agent/AgentContext.h>
#include <TheLastKnight/utils/fsm/BaseState.h>
#include <TheLastKnight/NAI/source/goap/GoapTypes.h>

namespace NAI
{
	namespace Goap
	{
		class IGoapPlanner;

		class Planning : public core::utils::FSM::BaseState<AgentState, AgentContext>
		{
		public:
			Planning() = default;
			virtual ~Planning() = default;
			AgentState GetID() const override { return AgentState::STATE_PLANNING; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;

		private:
			std::shared_ptr<IGoapPlanner> mGoapPlanner;
		};
	}
}
