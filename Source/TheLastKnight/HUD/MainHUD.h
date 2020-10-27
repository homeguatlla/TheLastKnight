// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include "MainHUD.generated.h"


class ACharacterHUD;
class ADebugHUDController;

/**
 * Basic Main HUD
 */
UCLASS()
class THELASTKNIGHT_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainHUD();

	void BeginPlay() override;

private:
	void BindToDelegate();
	void CreateDebugHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses);
	void CreateCharacterHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses);

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Character HUDs")
	TArray<TSubclassOf<UUserWidget>> CharacterHUDWidgetClasses;

	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Debug HUDs")
	TArray<TSubclassOf<UUserWidget>> DebugHUDWidgetClasses;

	UPROPERTY()
	UUserWidget* mCharacterHUDWidget;

	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	int mHudIndex;

	ACharacterHUD* mCharacterHUD;
	ADebugHUDController* mDebugHUDController;
};
