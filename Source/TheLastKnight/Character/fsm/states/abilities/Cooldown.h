#pragma once
#include <TheLastKnight/utils/fsm/BaseState.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class IAbility;

	class Cooldown : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Cooldown() = default;
		virtual ~Cooldown() = default;
		CharacterState GetID() const override { return CharacterState::STATE_COOLDOWN; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;
		void OnExit(float deltaTime) override;

	private:
		std::shared_ptr<TLN::IAbility> mAbility;
	};
};
