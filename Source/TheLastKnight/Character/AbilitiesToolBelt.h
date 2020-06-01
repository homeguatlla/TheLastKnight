#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Character/InputHandler.h>
#include <TheLastKnight/Abilities/IAbility.h>
#include <memory>
#include <vector>
#include <map>

class AAbility;
class UTexture2D;

namespace TLN
{
	class AbilitiesToolBelt
	{
		std::vector<std::shared_ptr<IAbility>> mAbilities;
		std::map<InputAction, int> mAbilitiesInToolBelt;

		public:
			AbilitiesToolBelt() = default;
			~AbilitiesToolBelt() = default;

			void Initialize();
			int AddAbility(std::shared_ptr<IAbility> ability);
			void BindAbilityToToolBelt(InputAction action, int index);
			bool CanCast(InputAction action, int availableMana) const;
			bool IsReadyToCast() const;
			std::shared_ptr<IAbility> GetAbility(InputAction action);
			const std::shared_ptr<IAbility> GetAbility(InputAction action) const;

	private:
		void NotifyAbilityAdded(AAbility* ability, UTexture2D* icon, int slot);
	};
};