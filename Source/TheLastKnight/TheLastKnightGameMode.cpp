// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheLastKnightGameMode.h"
#include "TheLastKnightCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheLastKnightGameMode::ATheLastKnightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TheLastKnight/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
