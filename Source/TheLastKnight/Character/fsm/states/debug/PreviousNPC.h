#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

class AEventDispatcher;

namespace TLN
{
	class CharacterContext;	

	class PreviousNPC : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		PreviousNPC() = default;
		virtual ~PreviousNPC() = default;
		CharacterState GetID() const override { return CharacterState::STATE_PREVIOUS_NPC; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		AEventDispatcher* mEventDispatcher;
	};
};
