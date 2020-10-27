#include <TheLastKnight/Character/fsm/transitions/debug/EnterDebug.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterDebug::EnterDebug(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterDebug::OnInit()
	{
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterDebug::CanPerformTransition() const
	{
		return mInputHandler->IsActionPressed(InputAction::ENTER_LEAVE_DEBUG);
	}
};