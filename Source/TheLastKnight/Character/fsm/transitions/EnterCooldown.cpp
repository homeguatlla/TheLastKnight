#include <TheLastKnight/Character/fsm/transitions/EnterCooldown.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Abilities/IAbility.h>


namespace TLN
{
	EnterCooldown::EnterCooldown(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterCooldown::OnInit()
	{
	}

	bool EnterCooldown::CanPerformTransition() const
	{
		return GetContext()->GetAbility() && !GetContext()->GetAbility()->IsCasting();
	}
};