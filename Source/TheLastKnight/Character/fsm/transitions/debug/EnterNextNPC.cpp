#include <TheLastKnight/Character/fsm/transitions/debug/EnterNextNPC.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterNextNPC::EnterNextNPC(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterNextNPC::OnInit()
	{
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterNextNPC::CanPerformTransition() const
	{
		auto pressed = mInputHandler->IsActionPressed(InputAction::NEXT_NPC);
		mInputHandler->InsertInput(InputAction::NEXT_NPC, false);

		return pressed;
	}
};