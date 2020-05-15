// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <string>
#include <TheLastKnight/Abilities/Ability.h>
#include "DA_CharacterAbility.generated.h"

/**
 * Holds Ability attributes
 */

UCLASS()
class THELASTKNIGHT_API UDA_CharacterAbility : public UPrimaryDataAsset
{
	GENERATED_BODY()

	/** Cost in mana to cast this ability */
	UPROPERTY(EditAnywhere, Category = "Character Ability")
	uint8 ManaCost;

	/** Cooldown time until the ability could be cast again */
	UPROPERTY(EditAnywhere, Category = "Character Ability")
	float CooldownTime;

	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Character Ability")
	TSubclassOf<AAbility> AbilityClass;

	UPROPERTY(EditAnywhere, Category = "Character Ability")
	FString LogicClassName;

public:
	uint8 GetManaCost() const { return ManaCost; }
	float GetCooldownTime() const { return CooldownTime; }
	TSubclassOf<AAbility> GetAbilityClass() const { return AbilityClass; }
	std::string GetLogicClassName() const { return std::string(TCHAR_TO_UTF8(*LogicClassName)); }
};
