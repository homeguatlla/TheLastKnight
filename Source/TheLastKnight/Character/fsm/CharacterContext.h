#pragma once
#include <memory>

namespace TLN
{
	class ICharacter;
	class CharacterContext
	{
	public:
		CharacterContext(TLN::ICharacter* character);
		~CharacterContext() = default;

		ICharacter* GetCharacter();

	private:
		ICharacter* mCharacter;
	};
};
