#include <TheLastKnight/Character/fsm/states/Cooldown.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Abilities/IAbility.h>

namespace TLN
{
	void Cooldown::OnInit()
	{
	}

	void Cooldown::OnEnter(float deltaTime)
	{
		mAbility = GetContext()->GetAbility();
	}

	void Cooldown::OnUpdate(float deltaTime)
	{
		mAbility->Update(deltaTime);
	}

	void Cooldown::OnExit(float deltaTime)
	{
		GetContext()->SetAbility(nullptr);
	}
};