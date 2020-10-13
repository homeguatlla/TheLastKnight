// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include "MainHUD.generated.h"

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

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "CharacterHUD")
	TSubclassOf<UUserWidget> CharacterHUDWidgetClass;

	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Debug HUD")
	TSubclassOf<UUserWidget> DebugHUDWidgetClass;

	UPROPERTY()
	UUserWidget* mCharacterHUDWidget;

	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	int mHudIndex;
};
