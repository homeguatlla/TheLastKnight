#include <TheLastKnight/Character/fsm/transitions/EnterJump.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterJump::EnterJump(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterJump::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterJump::CanPerformTransition() const
	{
		return false;
		//return mPlayer->IsActionActive(PlayerAction::Jump);
	}
}