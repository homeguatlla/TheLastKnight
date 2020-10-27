#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterRun : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterRun(StatePtr origin, StatePtr destination);
		virtual ~EnterRun() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};