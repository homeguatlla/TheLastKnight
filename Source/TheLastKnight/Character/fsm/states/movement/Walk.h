#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class ICharacter;

	class Walk : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Walk() = default;
		virtual ~Walk() = default;
		CharacterState GetID() const override { return CharacterState::STATE_WALKING; }
		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};

