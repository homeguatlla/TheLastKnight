#pragma once
#include <algorithm>

namespace TLN
{
	class CharacterAttributes
	{
	public:
		CharacterAttributes() = default;
		virtual ~CharacterAttributes() = default;

		unsigned int GetHealth() const { return mHealth; }
		unsigned int GetMana() const { return mMana; }

		void SetMaxHealth(unsigned int health) { mMaxHealth = health; mHealth = health; }
		void SetMaxMana(unsigned int mana) { mMaxMana = mana; mMana = mana; }
		void SetHealth(unsigned int health) { mHealth = std::min(std::max(0u, health), mMaxHealth); }
		void SetMana(unsigned int mana) { mMana = std::min(std::max(0u, mana), mMaxMana); }

	private:
		unsigned int mMaxHealth;
		unsigned int mMaxMana;
		unsigned int mHealth;
		unsigned int mMana;
	};
};