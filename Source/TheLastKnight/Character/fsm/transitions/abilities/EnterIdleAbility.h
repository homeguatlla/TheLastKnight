#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterIdleAbility : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterIdleAbility(StatePtr origin, StatePtr destination);
		virtual ~EnterIdleAbility() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};
