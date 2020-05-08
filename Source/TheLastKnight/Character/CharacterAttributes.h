#pragma once

class CharacterAttributes
{
public:
	CharacterAttributes() = default;
	virtual ~CharacterAttributes() = default;

	unsigned int GetHealth() const { return mHealth; }
	unsigned int GetMana() const { return mMana; }

	void SetMaxHealth(unsigned int health) { mMaxHealth = health; mHealth = health; }
	void SetMaxMana(unsigned int mana) { mMaxMana = mana; mMana = mana; }
	void SetHealth(unsigned int health) { mHealth = health; }
	void SetMana(unsigned int mana) { mMana = mana; }

private:
	unsigned int mMaxHealth;
	unsigned int mMaxMana;
	unsigned int mHealth;
	unsigned int mMana;
};
