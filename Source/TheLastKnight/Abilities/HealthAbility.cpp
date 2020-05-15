#include <TheLastKnight/Abilities/HealthAbility.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbility.h>
#include <TheLastKnight/Abilities/DataAssets/DA_HealthAbility.h>

namespace TLN
{
	HealthAbility::HealthAbility(AAbility* ability, UDA_CharacterAbility* abilityDA) :
		AbilityBase(abilityDA->GetManaCost(), abilityDA->GetCooldownTime()),
		mAAbility{ ability }
	{
		auto healthAbilityDA = dynamic_cast<UDA_HealthAbility*>(abilityDA);
		mPercentage = healthAbilityDA->GetHealPercentage();
	}

	std::shared_ptr<IAbility> HealthAbility::Create(AAbility* ability, UDA_CharacterAbility* abilityDA)
	{
		return std::make_shared<HealthAbility>(ability, abilityDA);
	}

	void HealthAbility::DoCast(const FVector& location)
	{
		if (mAAbility->IsValidLowLevel())
		{
			mAAbility->OnCast(location);
		}
	}
}