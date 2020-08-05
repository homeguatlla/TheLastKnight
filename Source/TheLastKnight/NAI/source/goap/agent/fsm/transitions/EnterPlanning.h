#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/NAI/source/goap/GoapTypes.h>
#include <TheLastKnight/NAI/source/goap/agent/AgentContext.h>

namespace NAI
{
	namespace Goap
	{
		class EnterPlanning : public core::utils::FSM::BaseTransition<AgentState, AgentContext>
		{
		public:
			EnterPlanning(StatePtr origin, StatePtr destination);
			virtual ~EnterPlanning() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
}
