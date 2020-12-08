#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext;

	class IdleAbility : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		IdleAbility() = default;
		virtual ~IdleAbility() = default;
		CharacterState GetID() const override { return CharacterState::STATE_IDLE_ABILITY; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};
