#pragma once
#include "CoreMinimal.h"
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <utility>

class UDA_CharacterAbilities;
class UDA_CharacterAbility;
class UWorld;
class ACharacter;
class AAbility;


namespace TLN
{
	class IAbility;

	class AbilitiesFactory
	{
		using AbilityFunctor = std::function < std::shared_ptr<IAbility>(AAbility*, UDA_CharacterAbility*)>;
		using AbilityData = std::pair<UDA_CharacterAbility*, AbilityFunctor>;
		std::map<std::string, AbilityData> mAbilities;

	public:
		AbilitiesFactory(const UDA_CharacterAbilities* abilities);

		void Register(const std::string& name, const AbilityFunctor& functor);
		std::shared_ptr<IAbility> Create(const std::string& name, UWorld* world, ACharacter* owner);

	private:
		bool FillWithAbilityData(const std::string& name, AbilityData& data);
	};
};