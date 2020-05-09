#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	CharacterContext::CharacterContext(TLN::ICharacter* character) : mCharacter {character}
	{
	}

	ICharacter* CharacterContext::GetCharacter()
	{
		return mCharacter;
	}
}