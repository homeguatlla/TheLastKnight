// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include <TheLastKnight/Debug/HUD/IDebugHUD.h>
#include "DebugHUDController.generated.h"

/**
 * Basic debug HUD
 */

UCLASS()
class THELASTKNIGHT_API ADebugHUDController : public AActor
{
	GENERATED_BODY()

public:
	ADebugHUDController();

	void Initialize(int hudIndex, APlayerController* playerController, TArray<TSubclassOf<UUserWidget>> DebugHUDWidgetClasses);
	
	UFUNCTION()
	void OnEnableDebugMode(bool enable);
	UFUNCTION()
	void OnLogPredicate(const ANPCAIController* controller, const FString& predicate);
	UFUNCTION()
	void OnLogClear(); 
	UFUNCTION()
	void OnNextNPC(const FString& name);
	UFUNCTION()
	void OnPreviousNPC(const FString& name);

private:
	void BindToDelegate();

public:
	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	UPROPERTY()
	UUserWidget* mAgentDebugHUDWidget;
};
