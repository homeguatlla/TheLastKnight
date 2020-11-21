#include <TheLastKnight/Character/fsm/transitions/debug/LeaveState.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	LeaveState::LeaveState(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	bool LeaveState::CanPerformTransition() const
	{
		return true;
	}
};