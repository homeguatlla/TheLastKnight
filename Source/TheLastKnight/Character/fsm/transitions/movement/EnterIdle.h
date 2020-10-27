#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterIdle : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterIdle(StatePtr origin, StatePtr destination);
		virtual ~EnterIdle() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};
