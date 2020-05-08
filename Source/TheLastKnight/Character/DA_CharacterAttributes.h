// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CharacterAttributes.generated.h"

/**
 * Basic character attributes, shared by all characters
 */
UCLASS()
class THELASTKNIGHT_API UDA_CharacterAttributes : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Character Attributes")
	uint8 MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Character Attributes")
	uint8 MaxMana;

public:
	uint8 GetMaxHealth() const { return MaxHealth; }
	uint8 GetMaxMana() const { return MaxMana; }
};
