#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/NAI/source/goap/GoapTypes.h>
#include <TheLastKnight/NAI/source/goap/agent/AgentContext.h>

namespace NAI
{
	namespace Goap
	{
		class EnterProcessing : public core::utils::FSM::BaseTransition<AgentState, AgentContext>
		{
		public:
			EnterProcessing(StatePtr origin, StatePtr destination);
			virtual ~EnterProcessing() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
}
