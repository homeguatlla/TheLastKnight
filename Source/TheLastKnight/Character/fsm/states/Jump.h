#pragma once
#include <TheLastKnight/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>


namespace TLN
{
	class CharacterContext;
	class ICharacter;

	class Jump : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Jump() = default;
		virtual ~Jump() = default;
		CharacterState GetID() const override { return CharacterState::STATE_JUMPING; }
		void OnInit() override;
		void OnEnter(float deltaTime) override;


	private:
		ICharacter* mCharacter;
	};
};

