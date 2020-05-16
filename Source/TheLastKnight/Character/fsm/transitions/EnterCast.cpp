#include <TheLastKnight/Character/fsm/transitions/EnterCast.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterCast::EnterCast(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterCast::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterCast::CanPerformTransition() const
	{
		bool isAbilityPressed = false;
		InputAction actionToCast;

		if (mInputHandler->IsActionPressed(InputAction::ABILITY1))
		{
			actionToCast = InputAction::ABILITY1;
			isAbilityPressed = true;
		}
		else if (mInputHandler->IsActionPressed(InputAction::ABILITY2))
		{
			actionToCast = InputAction::ABILITY2;
			isAbilityPressed = true;
		}
		
		return isAbilityPressed && mCharacter->CanCast(actionToCast);
	}
};