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
		auto pressed = mInputHandler->IsActionPressed(InputAction::ENTER_LEAVE_DEBUG);

		mInputHandler->InsertInput(InputAction::ENTER_LEAVE_DEBUG, false);

		return pressed;
	}
};