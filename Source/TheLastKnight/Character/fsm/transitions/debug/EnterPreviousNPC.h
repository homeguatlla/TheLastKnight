#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class InputHandler;

	class EnterPreviousNPC : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterPreviousNPC(StatePtr origin, StatePtr destination);
		virtual ~EnterPreviousNPC() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		std::shared_ptr<InputHandler> mInputHandler;
	};
};
