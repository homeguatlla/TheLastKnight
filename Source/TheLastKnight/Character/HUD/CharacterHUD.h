// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
//#include <TheLastKnight/Character/HUD/IInterfaceHUD.h>
#include "CharacterHUD.generated.h"



/**
 * Basic character HUD
 */
UCLASS()
class THELASTKNIGHT_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACharacterHUD();

	void BeginPlay() override;
	
	UFUNCTION()
	void OnUpdateHealthReceived(float health);

	//inherit from IInterfaceHUD
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnUpdateHealth(float health);

private:
	void BindToDelegate();

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* mHUDWidget;
};
