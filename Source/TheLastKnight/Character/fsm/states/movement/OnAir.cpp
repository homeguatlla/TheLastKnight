#include <TheLastKnight/Character/fsm/states/movement/OnAir.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	void OnAir::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void OnAir::OnEnter(float deltaTime)
	{
	}
};