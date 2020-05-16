#include <TheLastKnight/Character/AbilitiesToolChest.h>

namespace TLN
{
	int AbilitiesToolChest::AddAbility(std::shared_ptr<IAbility> ability)
	{
		//TODO exist?
		mAbilities.push_back(ability);

		return mAbilities.size() - 1;
	}

	void AbilitiesToolChest::BindAbilityToToolBelt(InputAction action, int index)
	{
		//TODO exist ability with index??
		mAbilitiesInToolBelt[action] = index;
	}

	bool AbilitiesToolChest::IsReadyToCast() const
	{
		for (auto&& ability : mAbilitiesInToolBelt)
		{
			if (!mAbilities[ability.second]->IsReadyToCast())
			{
				return false;
			}
		}
		return true;
	}

	bool AbilitiesToolChest::CanCast(InputAction action, int availableMana) const
	{
		auto ability = GetAbility(action);
		if (ability != nullptr)
		{
			return ability->CanCast(availableMana);
		}
		else
		{
			return false;
		}
	}

	std::shared_ptr<IAbility> AbilitiesToolChest::GetAbility(InputAction action)
	{
		return std::const_pointer_cast<IAbility>(const_cast<const AbilitiesToolChest*>(this)->GetAbility(action));
		
	}

	const std::shared_ptr<IAbility> AbilitiesToolChest::GetAbility(InputAction action) const
	{
		auto it = mAbilitiesInToolBelt.find(action);
		if (it != std::end(mAbilitiesInToolBelt))
		{
			return mAbilities[it->second];
		}
		else
		{
			return nullptr;
		}
	}
}