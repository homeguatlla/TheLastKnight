// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <TheLastKnight/EventDispatcher.h>
#include "TheLastKnightGameMode.generated.h"

const float NavigationPointsPrecision = 100.0f;

UCLASS(minimalapi)
class ATheLastKnightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheLastKnightGameMode();

	AEventDispatcher* GetEventDispatcher() { return mEventDispatcher; }

	/** Blueprint class which manage events with HUD */
	UPROPERTY(EditAnywhere, Category = "HUD Event Dispatcher")
	TSubclassOf<AEventDispatcher> HUDEventDispatcherClass;

protected:
	void BeginPlay() override;

private:
	AEventDispatcher* mEventDispatcher;
};



