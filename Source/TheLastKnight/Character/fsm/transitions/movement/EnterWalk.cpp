#include <TheLastKnight/Character/fsm/transitions/movement/EnterWalk.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterWalk::EnterWalk(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterWalk::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterWalk::CanPerformTransition() const
	{
		return mCharacter->IsWalking() && !mCharacter->IsCasting();
	}
}