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
		mCharacter->PlayCastingAnimation();
		mAbility = mCharacter->Cast();
		GetContext()->SetAbility(mAbility);
	}

	void Casting::OnUpdate(float deltaTime)
	{
		mAbility->Update(deltaTime);
	}

	void Casting::OnExit(float deltaTime)
	{
		mCharacter->StopCastingAnimation();
	}
};