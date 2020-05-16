#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>

namespace TLN
{
	CharacterContext::CharacterContext(TLN::ICharacter* character, std::shared_ptr<InputHandler> input) :
		mCharacter {character},
		mInputHandler {input}
	{
	}

	ICharacter* CharacterContext::GetCharacter()
	{
		return mCharacter;
	}

	std::shared_ptr<InputHandler> CharacterContext::GetInputHandler()
	{
		return mInputHandler;
	}

	void CharacterContext::SetAbility(std::shared_ptr<IAbility> ability)
	{
		mAbility = ability;
	}
}