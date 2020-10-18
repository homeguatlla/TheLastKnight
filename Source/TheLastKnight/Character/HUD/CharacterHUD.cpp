// Fill out your copyright notice in the Description page of Project Settings.


#include <TheLastKnight/Character/HUD/CharacterHUD.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Character/HUD/IHealthHUD.h>
#include <TheLastKnight/Character/HUD/Abilities/IAbilityBaseHUD.h>
#include <Kismet/GameplayStatics.h>
#include <TheLastKnight/utils/UtilsLibrary.h>

const FString CHARACTER_HUD_NAME("CharacterHUD");

ACharacterHUD::ACharacterHUD()
{

}

void ACharacterHUD::Initialize(
	int hudIndex, 
	APlayerController* playerController, 
	TArray<TSubclassOf<UUserWidget>> widgetsClasses)
{
/*
	mCharacterHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++,
		CHARACTER_HUD_NAME,
		playerController,
		widgetsClasses[0]);*/

	mHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		CHARACTER_HUD_NAME,
		playerController,
		widgetsClasses[0]);
	mAbilitiesToolBeltHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		CHARACTER_HUD_NAME,
		playerController,
		widgetsClasses[1]);

	BindToDelegate();
}

void ACharacterHUD::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));
	if (gameMode)
	{
		gameMode->GetEventDispatcher()->OnUpdateHealth.AddDynamic(this, &ACharacterHUD::OnUpdateHealthReceived);
		gameMode->GetEventDispatcher()->OnAddAbilityIntoToolBelt.AddDynamic(this, &ACharacterHUD::OnAddAbilityIntoToolBeltReceived);

		gameMode->GetEventDispatcher()->OnNotifyStartCasting.AddDynamic(this, &ACharacterHUD::OnNotifyStartCastingReceived);
		gameMode->GetEventDispatcher()->OnNotifyCast.AddDynamic(this, &ACharacterHUD::OnNotifyCastReceived);
		gameMode->GetEventDispatcher()->OnNotifyCooldownTime.AddDynamic(this, &ACharacterHUD::OnNotifyCooldownTimeReceived);
		gameMode->GetEventDispatcher()->OnNotifyReadyToCast.AddDynamic(this, &ACharacterHUD::OnNotifyReadyToCastReceived);
	}
}

void ACharacterHUD::OnUpdateHealthReceived(float health)
{
	if (mHUDWidget->GetClass()->ImplementsInterface(UHealthHUD::StaticClass()))
	{
		IHealthHUD::Execute_OnUpdateHealth(mHUDWidget, health);
	}
}

void ACharacterHUD::OnAddAbilityIntoToolBeltReceived(const FString& name, UTexture2D* icon, int slot)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilitiesToolBeltHUD::Execute_OnAddAbilityIntoToolBelt(mAbilitiesToolBeltHUDWidget, name, icon, slot);
	}
}

void ACharacterHUD::OnNotifyStartCastingReceived(const FString& name)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilityBaseHUD::Execute_OnNotifyStartCasting(mAbilitiesToolBeltHUDWidget, name);
	}
}

void ACharacterHUD::OnNotifyCastReceived(const FString& name)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilityBaseHUD::Execute_OnNotifyCast(mAbilitiesToolBeltHUDWidget, name);
	}
}

void ACharacterHUD::OnNotifyCooldownTimeReceived(const FString& name, float remainingTime)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilityBaseHUD::Execute_OnNotifyCooldownTime(mAbilitiesToolBeltHUDWidget, name, remainingTime);
	}
}

void ACharacterHUD::OnNotifyReadyToCastReceived(const FString& name)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilityBaseHUD::Execute_OnNotifyReadyToCast(mAbilitiesToolBeltHUDWidget, name);
	}
}