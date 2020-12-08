#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class OnAir : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		OnAir() = default;
		virtual ~OnAir() = default;
		CharacterState GetID() const override { return CharacterState::STATE_ON_AIR; }
		void OnInit() override;
		void OnEnter(float deltaTime) override;


	private:
		ICharacter* mCharacter;
	};
};

