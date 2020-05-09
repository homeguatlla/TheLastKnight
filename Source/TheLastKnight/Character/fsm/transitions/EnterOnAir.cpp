#include <TheLastKnight/Character/fsm/transitions/EnterOnAir.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterOnAir::EnterOnAir(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterOnAir::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterOnAir::CanPerformTransition() const
	{
		return false;
	}
}