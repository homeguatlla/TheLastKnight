// Fill out your copyright notice in the Description page of Project Settings.


#include <TheLastKnight/HUD/MainHUD.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/HUD/Debug/IAgentDebugHUD.h>
#include <Kismet/GameplayStatics.h>


AMainHUD::AMainHUD() : mHudIndex{0}
{

}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	mCharacterHUDWidget = CreateHUDFromClass<UUserWidget>(CharacterHUDWidgetClass);
	mDebugHUDWidget = CreateHUDFromClass<UUserWidget>(DebugHUDWidgetClass);

	BindToDelegate();
}

void AMainHUD::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(GetOwningPawn()->GetWorld()));
	if (gameMode)
	{
		gameMode->GetEventDispatcher()->OnLogPredicate.AddDynamic(this, &AMainHUD::OnLogPredicate);
		
		/*gameMode->GetEventDispatcher()->OnUpdateHealth.AddDynamic(this, &ACharacterHUD::OnUpdateHealthReceived);
		gameMode->GetEventDispatcher()->OnAddAbilityIntoToolBelt.AddDynamic(this, &ACharacterHUD::OnAddAbilityIntoToolBeltReceived);

		gameMode->GetEventDispatcher()->OnNotifyStartCasting.AddDynamic(this, &ACharacterHUD::OnNotifyStartCastingReceived);
		gameMode->GetEventDispatcher()->OnNotifyCast.AddDynamic(this, &ACharacterHUD::OnNotifyCastReceived);
		gameMode->GetEventDispatcher()->OnNotifyCooldownTime.AddDynamic(this, &ACharacterHUD::OnNotifyCooldownTimeReceived);
		gameMode->GetEventDispatcher()->OnNotifyReadyToCast.AddDynamic(this, &ACharacterHUD::OnNotifyReadyToCastReceived);*/
	}
}

void AMainHUD::OnLogPredicate(const FString& predicate)
{
	if (mDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogPredicate(mDebugHUDWidget, predicate);
	}
}