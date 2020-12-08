#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext;

	class Idle : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Idle() = default;
		virtual ~Idle() = default;
		CharacterState GetID() const override { return CharacterState::STATE_IDLE; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};
