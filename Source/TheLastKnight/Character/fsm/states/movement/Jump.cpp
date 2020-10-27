#include <TheLastKnight/Character/fsm/states/movement/Jump.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	void Jump::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Jump::OnEnter(float deltaTime)
	{
		//mCharacter->PerformJump(deltaTime);
	}
};
