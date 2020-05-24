// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheLastKnightGameMode.h"
#include "TheLastKnightCharacter.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

ATheLastKnightGameMode::ATheLastKnightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TheLastKnight/Blueprints/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default HUD class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AHUD> CharacterHUDBPClass(TEXT("/Game/TheLastKnight/Blueprints/Character/HUD/BP_CharacterHUD"));
	if (CharacterHUDBPClass.Class != NULL)
	{
		HUDClass = CharacterHUDBPClass.Class;
	}
}

void ATheLastKnightGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	mEventDispatcher = GetWorld()->SpawnActor<AEventDispatcher>(
		AEventDispatcher::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);

	mEventDispatcher->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
}
