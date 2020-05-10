#pragma once
#include <memory>
#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext
	{
	public:
		CharacterContext(ICharacter* character, std::shared_ptr<InputHandler> input);
		~CharacterContext() = default;

		ICharacter* GetCharacter();
		std::shared_ptr<InputHandler> GetInputHandler();

	private:
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
	};
};
