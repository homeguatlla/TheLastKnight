// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include <TheLastKnight/Character/HUD/Abilities/IAbilitiesToolBeltHUD.h>
#include "CharacterHUD.generated.h"

/**
 * Basic character HUD
 */

UCLASS()
class THELASTKNIGHT_API ACharacterHUD : public AActor
{
	GENERATED_BODY()

public:
	ACharacterHUD();

	void Initialize(int hudIndex, APlayerController* playerController, TArray<TSubclassOf<UUserWidget>> CharacterHUDWidgetClasses);
	
	UFUNCTION()
	void OnUpdateHealthReceived(float health);
	UFUNCTION()
	void OnAddAbilityIntoToolBeltReceived(const FString& name, UTexture2D* icon, int slot);

	UFUNCTION()
	void OnNotifyStartCastingReceived(const FString& name);
	UFUNCTION()
	void OnNotifyCastReceived(const FString& name);
	UFUNCTION()
	void OnNotifyCooldownTimeReceived(const FString& name, float remainingTime);
	UFUNCTION()
	void OnNotifyReadyToCastReceived(const FString& name);

	//inherit from IHealthHUD
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnUpdateHealth(float health);

	//inherit from IAbilitiesToolBeltHUD
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Tool Belt")
	void OnAddAbilityIntoToolBelt(const FString& name, UTexture2D* icon, int slot);

	//inherit from AbilityBase
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyStartCasting(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyCast(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyCooldownTime(const FString& name, float remainingTime);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
	void OnNotifyReadyToCast(const FString& name);

private:
	void BindToDelegate();

public:
	UPROPERTY()
	UUserWidget* mHUDWidget;

	UPROPERTY()
	UUserWidget* mAbilitiesToolBeltHUDWidget;
};
