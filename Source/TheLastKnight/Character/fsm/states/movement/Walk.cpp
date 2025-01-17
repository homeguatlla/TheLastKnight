#include <TheLastKnight/Character/fsm/states/movement/Walk.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	void Walk::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Walk::OnEnter(float deltaTime)
	{
	}

	void Walk::OnUpdate(float deltaTime)
	{
		mCharacter->PerformMovement();
	}
};

