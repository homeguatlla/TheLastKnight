// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CharacterAbilities.generated.h"

/**
 * List of all abilities available for the character
 */

class UDA_CharacterAbility;

UCLASS()
class THELASTKNIGHT_API UDA_CharacterAbilities : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Character Abilities")
	TArray<UDA_CharacterAbility*> Abilities;

public:
	TArray<UDA_CharacterAbility*> GetAbilities() const { return Abilities; }
};
