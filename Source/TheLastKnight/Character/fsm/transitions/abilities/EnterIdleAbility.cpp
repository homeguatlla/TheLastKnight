#include <TheLastKnight/Character/fsm/transitions/abilities/EnterIdleAbility.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterIdleAbility::EnterIdleAbility(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterIdleAbility::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterIdleAbility::CanPerformTransition() const
	{
		return mCharacter->IsReadyToCast();
	}
};