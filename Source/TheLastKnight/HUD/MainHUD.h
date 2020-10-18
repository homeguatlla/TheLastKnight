// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include "MainHUD.generated.h"


class ACharacterHUD;

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

	UFUNCTION()
	void OnLogPredicate(const FString& predicate);
	
	UFUNCTION()
	void OnLogClear();

private:
	void BindToDelegate();
	void CreateCharacterHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses);

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Character HUD")
	TArray<TSubclassOf<UUserWidget>> CharacterHUDWidgetClasses;

	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Debug HUD")
	TSubclassOf<UUserWidget> DebugHUDWidgetClass;

	UPROPERTY()
	UUserWidget* mCharacterHUDWidget;

	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	int mHudIndex;

	ACharacterHUD* mCharacterHUD;
};
