// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include "CharacterHUD.generated.h"

/**
 * Basic character HUD
 */
UCLASS()
class THELASTKNIGHT_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* mHUDWidget;

	ACharacterHUD();

	void BeginPlay() override;
};
