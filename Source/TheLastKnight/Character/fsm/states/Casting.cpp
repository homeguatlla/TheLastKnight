#include <TheLastKnight/Character/fsm/states/Casting.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	void Casting::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Casting::OnEnter(float deltaTime)
	{
		mCharacter->Cast();
	}
};