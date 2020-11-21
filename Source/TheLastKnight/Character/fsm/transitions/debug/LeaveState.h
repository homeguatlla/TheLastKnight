#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;

	class LeaveState : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		LeaveState(StatePtr origin, StatePtr destination);
		virtual ~LeaveState() = default;

		bool CanPerformTransition() const override;
	};
};
