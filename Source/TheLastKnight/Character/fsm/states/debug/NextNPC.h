#pragma once
#include <TheLastKnight/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

class AEventDispatcher;

namespace TLN
{
	class CharacterContext;	

	class NextNPC : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		NextNPC() = default;
		virtual ~NextNPC() = default;
		CharacterState GetID() const override { return CharacterState::STATE_NEXT_NPC; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		AEventDispatcher* mEventDispatcher;
	};
};
