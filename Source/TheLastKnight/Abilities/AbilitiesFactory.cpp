#include "AbilitiesFactory.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include <TheLastKnight/Abilities/IAbility.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/Abilities/HealthAbility.h>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbilities.h>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbility.h>
#include <cassert>

namespace TLN
{
	AbilitiesFactory::AbilitiesFactory(const UDA_CharacterAbilities* abilities)
	{
		assert(abilities);

		if (abilities)
		{
			auto abilitiesDA = abilities->GetAbilities();
			for (int i = 0; i < abilitiesDA.Num(); ++i)
			{
				AbilityData data{ abilitiesDA[i], {} };
				mAbilities.insert(std::make_pair(abilitiesDA[i]->GetLogicClassName(), data));
			}
		}
	}

	void AbilitiesFactory::Register(const std::string& name, const AbilityFunctor& functor)
	{
		auto it = mAbilities.find(name);
		if (it != std::end(mAbilities))
		{
			it->second.second = functor;
		}
	}

	std::shared_ptr<IAbility> AbilitiesFactory::Create(const std::string& name, UWorld* world, ACharacter* owner)
	{
		std::pair<UDA_CharacterAbility*, AbilityFunctor> abilityData;
		
		if (FillWithAbilityData(name, abilityData))
		{
			FActorSpawnParameters spawnInfo;
			spawnInfo.Owner = owner;
			spawnInfo.Instigator = owner;
			spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			assert(abilityDA);
			assert(abilityFunctor);
			
			auto abilityBP = world->SpawnActor<AAbility>(
				abilityData.first->GetAbilityClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				spawnInfo);

			abilityBP->AttachToActor(owner, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

			auto ability = abilityData.second(abilityBP, abilityData.first);

			return ability;
		}

		return {};
	}

	bool AbilitiesFactory::FillWithAbilityData(const std::string& name, AbilityData& data)
	{
		auto it = mAbilities.find(name);
		if (it != std::end(mAbilities))
		{
			data = it->second;
			return true;
		}
		else
		{
			return false;
		}
	}
}