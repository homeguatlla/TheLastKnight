#pragma once
#include "agent/IAgent.h"
#include "agent/AgentContext.h"

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
		class BaseAgent : public IAgent
		{
		public:
			BaseAgent() = default;
			virtual ~BaseAgent() = default;

		private:
			core::utils::FSM::StatesMachine<AgentState, AgentContext>  mStatesMachine;
		};
	}
}

