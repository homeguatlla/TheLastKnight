#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterOnAir : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterOnAir(StatePtr origin, StatePtr destination);
		virtual ~EnterOnAir() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};