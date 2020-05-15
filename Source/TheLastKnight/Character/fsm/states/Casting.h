#pragma once
#include <TheLastKnight/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext;
	class IAbility;

	class Casting : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Casting() = default;
		virtual ~Casting() = default;
		CharacterState GetID() const override { return CharacterState::STATE_CASTING; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;

	private:
		ICharacter* mCharacter;
		std::shared_ptr<TLN::IAbility> mAbility;
	};
};
