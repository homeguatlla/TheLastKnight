#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/AbilitityBase.h>
#include <string>
#include <memory>

class AAbility;
class UDA_CharacterAbility;

namespace TLN
{
	class HealthAbility : public AbilityBase
	{
		float mPercentage;
		AAbility* mAAbility;

	public:
		HealthAbility(AAbility* ability, UDA_CharacterAbility* abilityDA);
		static std::string GetName() { return "HealthAbility"; }
		static std::shared_ptr<IAbility> Create(AAbility* ability, UDA_CharacterAbility* abilityDA);
		void DoCast(const FVector& location) override;
	};
};