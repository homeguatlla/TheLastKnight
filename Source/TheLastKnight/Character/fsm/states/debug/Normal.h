#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

class AEventDispatcher;

namespace TLN
{
	class CharacterContext;

	class Normal : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Normal() = default;
		virtual ~Normal() = default;
		CharacterState GetID() const override { return CharacterState::STATE_NORMAL; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;
	
	private:
		AEventDispatcher* mEventDispatcher;
	};
};
