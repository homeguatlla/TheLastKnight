#include <TheLastKnight/Character/fsm/states/Casting.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Abilities/IAbility.h>

namespace TLN
{
	void Casting::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Casting::OnEnter(float deltaTime)
	{
		mAbility = mCharacter->Cast();
	}

	void Casting::OnUpdate(float deltaTime)
	{
		mAbility->Update(deltaTime);
	}
};