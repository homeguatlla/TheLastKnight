#pragma once
#include <TheLastKnight/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;
	class InputHandler;

	class EnterCast : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterCast(StatePtr origin, StatePtr destination);
		virtual ~EnterCast() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
	};
};
