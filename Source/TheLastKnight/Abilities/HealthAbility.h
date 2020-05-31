#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/AbilitityBase.h>
#include <string>
#include <memory>


class AAbility;
class UTexture2D;
class UDA_CharacterAbility;

namespace TLN
{
	class CharacterAttributes;

	class HealthAbility : public AbilityBase
	{
		float mPercentage;
		AAbility* mAAbility;
		std::shared_ptr<TLN::CharacterAttributes> mCharacterAttributes;
		UDA_CharacterAbility* mAbilityDA;

	public:
		HealthAbility(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes);
		virtual ~HealthAbility() = default;
		static std::string GetName() { return "HealthAbility"; }
		static std::shared_ptr<IAbility> Create(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes);
		void DoStartCasting(const FVector& location) override;
		void DoCastSpell() override;

		AAbility* GetAbilityActor() const  override { return mAAbility; }
		UTexture2D* GetIcon() const  override;

	private:
		void IncrementLife();
		void NotifyUpdateHealth();
	};
};