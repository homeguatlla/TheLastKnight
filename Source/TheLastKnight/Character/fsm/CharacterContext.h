#pragma once
#include <memory>
#include <TheLastKnight/Character/InputHandler.h>

class AEventDispatcher;
class UWorld;

namespace TLN
{
	class ICharacter;
	class IAbility;

	class CharacterContext
	{
	public:
		CharacterContext(UWorld* world, ICharacter* character, std::shared_ptr<InputHandler> input);
		~CharacterContext() = default;

		ICharacter* GetCharacter();
		std::shared_ptr<InputHandler> GetInputHandler();
		AEventDispatcher* GetEventDispatcher();

		void SetAbility(std::shared_ptr<IAbility> ability);
		std::shared_ptr<IAbility> GetAbility() { return mAbility; }

	private:
		UWorld* mWorld;
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
		std::shared_ptr<IAbility> mAbility;
		AEventDispatcher* mEventDispatcher;
	};
};
