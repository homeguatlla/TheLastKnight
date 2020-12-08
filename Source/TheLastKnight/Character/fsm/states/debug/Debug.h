#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

class AEventDispatcher;

namespace TLN
{
	class ICharacter;
	class CharacterContext;	

	class Debug : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Debug() = default;
		virtual ~Debug() = default;
		CharacterState GetID() const override { return CharacterState::STATE_DEBUG; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		AEventDispatcher* mEventDispatcher;
	};
};
