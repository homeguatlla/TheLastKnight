// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <string>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbility.h>
#include "DA_HealthAbility.generated.h"

/**
 * Holds Ability attributes
 */

class AAbility;

UCLASS()
class THELASTKNIGHT_API UDA_HealthAbility : public UDA_CharacterAbility
{
	GENERATED_BODY()

	/** Percentage from 0 to 1 of character live to recover */
	UPROPERTY(EditAnywhere, Category = "Health Ability")
	float HealPercentage;

public:
	float GetHealPercentage() const { return HealPercentage; }
};
