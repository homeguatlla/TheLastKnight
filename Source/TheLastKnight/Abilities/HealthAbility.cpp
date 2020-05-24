#include <TheLastKnight/Abilities/HealthAbility.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbility.h>
#include <TheLastKnight/Abilities/DataAssets/DA_HealthAbility.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Character/CharacterAttributes.h>

namespace TLN
{
	HealthAbility::HealthAbility(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes) :
		AbilityBase(abilityDA->GetManaCost(), abilityDA->GetCastingTime(), abilityDA->GetCooldownTime()),
		mAAbility{ ability },
		mCharacterAttributes { attributes }
	{
		auto healthAbilityDA = dynamic_cast<UDA_HealthAbility*>(abilityDA);
		mPercentage = healthAbilityDA->GetHealPercentage();
	}

	std::shared_ptr<IAbility> HealthAbility::Create(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes)
	{
		return std::make_shared<HealthAbility>(ability, abilityDA, attributes);
	}

	void HealthAbility::DoStartCasting(const FVector& location)
	{
		if (mAAbility->IsValidLowLevel())
		{
			mAAbility->OnStartCasting(location);
		}
	}

	void HealthAbility::DoCastSpell()
	{
		IncrementLife();
		NotifyUpdateHealth();		

		if (mAAbility->IsValidLowLevel())
		{
			mAAbility->OnCast();
		}
	}

	void HealthAbility::NotifyUpdateHealth()
	{
		auto gameMode = mAAbility->GetWorld()->GetAuthGameMode<ATheLastKnightGameMode>();
		if (gameMode->IsValidLowLevel())
		{
			gameMode->GetEventDispatcher()->OnUpdateHealth.Broadcast(mCharacterAttributes->GetHealth());
		}
	}

	void HealthAbility::IncrementLife()
	{
		float newHealth = mCharacterAttributes->GetHealth() + mCharacterAttributes->GetHealth() * mPercentage;
		mCharacterAttributes->SetHealth(newHealth);
	}
}