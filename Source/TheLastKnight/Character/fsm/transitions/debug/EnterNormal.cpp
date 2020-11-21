#include <TheLastKnight/Character/fsm/transitions/debug/EnterNormal.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterNormal::EnterNormal(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterNormal::OnInit()
	{
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterNormal::CanPerformTransition() const
	{
		auto pressed = mInputHandler->IsActionPressed(InputAction::ENTER_LEAVE_DEBUG);
		mInputHandler->InsertInput(InputAction::ENTER_LEAVE_DEBUG, false);

		return pressed;
	}
};