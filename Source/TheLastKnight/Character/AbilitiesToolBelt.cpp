#include <TheLastKnight/Character/AbilitiesToolBelt.h>
#include <TheLastKnight/EventDispatcher.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <algorithm>


namespace TLN
{
	int AbilitiesToolBelt::AddAbility(std::shared_ptr<IAbility> ability)
	{
		int index = -1;

		auto it = std::find_if(
			mAbilities.begin(), 
			mAbilities.end(), 
			[&ability](const std::shared_ptr<IAbility> a) 
			{
				return a->GetAbilityActor() == ability->GetAbilityActor();
			});

		if (it == std::end(mAbilities))
		{
			mAbilities.push_back(ability);
			index = mAbilities.size() - 1;
		}

		return index;
	}

	void AbilitiesToolBelt::Initialize()
	{
		for (int index = 0; index < mAbilities.size(); index++)
		{
			auto ability = mAbilities[index];
			NotifyAbilityAdded(ability->GetAbilityActor(), ability->GetIcon(), index);
		}
	}

	void AbilitiesToolBelt::NotifyAbilityAdded(AAbility* ability, UTexture2D* icon, int slot)
	{
		auto gameMode = ability->GetWorld()->GetAuthGameMode<ATheLastKnightGameMode>();
		if (gameMode->IsValidLowLevel())
		{
			gameMode->GetEventDispatcher()->OnAddAbilityIntoToolBelt.Broadcast(ability->GetName(), icon, slot);
		}
	}

	void AbilitiesToolBelt::BindAbilityToToolBelt(InputAction action, int index)
	{
		//TODO exist ability with index??
		mAbilitiesInToolBelt[action] = index;
	}

	bool AbilitiesToolBelt::IsReadyToCast() const
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

	bool AbilitiesToolBelt::CanCast(InputAction action, int availableMana) const
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

	std::shared_ptr<IAbility> AbilitiesToolBelt::GetAbility(InputAction action)
	{
		return std::const_pointer_cast<IAbility>(const_cast<const AbilitiesToolBelt*>(this)->GetAbility(action));
		
	}

	const std::shared_ptr<IAbility> AbilitiesToolBelt::GetAbility(InputAction action) const
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