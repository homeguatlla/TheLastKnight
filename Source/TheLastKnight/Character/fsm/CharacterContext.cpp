#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/TheLastKnightGameMode.h>

namespace TLN
{
	CharacterContext::CharacterContext(UWorld* world, TLN::ICharacter* character, std::shared_ptr<InputHandler> input) :
		mWorld {world},
		mCharacter {character},
		mInputHandler {input}
	{
		auto gameMode = world->GetAuthGameMode<ATheLastKnightGameMode>();
		if (gameMode->IsValidLowLevel())
		{
			mEventDispatcher = gameMode->GetEventDispatcher();
		}
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

	AEventDispatcher* CharacterContext::GetEventDispatcher()
	{
		return mEventDispatcher;
	}
}