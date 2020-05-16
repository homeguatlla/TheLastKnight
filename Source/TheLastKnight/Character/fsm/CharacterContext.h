#pragma once
#include <memory>
#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
	class ICharacter;
	class IAbility;

	class CharacterContext
	{
	public:
		CharacterContext(ICharacter* character, std::shared_ptr<InputHandler> input);
		~CharacterContext() = default;

		ICharacter* GetCharacter();
		std::shared_ptr<InputHandler> GetInputHandler();

		void SetAbility(std::shared_ptr<IAbility> ability);
		std::shared_ptr<IAbility> GetAbility() { return mAbility; }

	private:
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
		std::shared_ptr<IAbility> mAbility;
	};
};
