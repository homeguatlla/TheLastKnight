// Fill out your copyright notice in the Description page of Project Settings.


#include <TheLastKnight/Character/HUD/CharacterHUD.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Character/HUD/IHealthHUD.h>
#include <Kismet/GameplayStatics.h>


ACharacterHUD::ACharacterHUD() : mHudIndex{0}
{

}

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	mHUDWidget = CreateHUDFromClass<UUserWidget>(HUDWidgetClass);
	mAbilitiesToolBeltHUDWidget = CreateHUDFromClass<UUserWidget>(AbilitiesToolBeltHUDWidgetClass);

	BindToDelegate();
}

void ACharacterHUD::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(GetOwningPawn()->GetWorld()));
	if (gameMode)
	{
		gameMode->GetEventDispatcher()->OnUpdateHealth.AddDynamic(this, &ACharacterHUD::OnUpdateHealthReceived);
		gameMode->GetEventDispatcher()->OnAddAbilityIntoToolBelt.AddDynamic(this, &ACharacterHUD::OnAddAbilityIntoToolBeltReceived);
	}
}

void ACharacterHUD::OnUpdateHealthReceived(float health)
{
	if (mHUDWidget->GetClass()->ImplementsInterface(UHealthHUD::StaticClass()))
	{
		IHealthHUD::Execute_OnUpdateHealth(mHUDWidget, health);
	}
}

void ACharacterHUD::OnAddAbilityIntoToolBeltReceived(UTexture2D* icon, int slot)
{
	if (mAbilitiesToolBeltHUDWidget->GetClass()->ImplementsInterface(UAbilitiesToolBeltHUD::StaticClass()))
	{
		IAbilitiesToolBeltHUD::Execute_OnAddAbilityIntoToolBelt(mAbilitiesToolBeltHUDWidget, icon, slot);
	}
}