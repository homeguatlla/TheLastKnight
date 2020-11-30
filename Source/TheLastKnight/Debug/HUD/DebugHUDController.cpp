// Fill out your copyright notice in the Description page of Project Settings.
#include <TheLastKnight/Debug/HUD/DebugHUDController.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Debug/HUD/IDebugHUD.h>
#include <TheLastKnight/Debug/HUD/IAgentDebugHUD.h>
#include <Kismet/GameplayStatics.h>
#include <TheLastKnight/utils/UtilsLibrary.h>

const FString DEBUG_HUD_NAME("DebugHUDController");

ADebugHUDController::ADebugHUDController()
{

}

void ADebugHUDController::Initialize(
	int hudIndex, 
	APlayerController* playerController, 
	TArray<TSubclassOf<UUserWidget>> widgetsClasses)
{
	mDebugHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		DEBUG_HUD_NAME,
		playerController,
		widgetsClasses[0]);
	mAgentDebugHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		DEBUG_HUD_NAME,
		playerController,
		widgetsClasses[1]);

	BindToDelegate();
}

void ADebugHUDController::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));
	if (gameMode)
	{
		auto eventDispatcher = gameMode->GetEventDispatcher();

		eventDispatcher->OnEnableDebugMode.AddDynamic(this, &ADebugHUDController::OnEnableDebugMode);
		eventDispatcher->OnLogPredicate.AddDynamic(this, &ADebugHUDController::OnLogPredicate);
		eventDispatcher->OnLogClear.AddDynamic(this, &ADebugHUDController::OnLogClear);
		eventDispatcher->OnNextNPC.AddDynamic(this, &ADebugHUDController::OnNextNPC);
		eventDispatcher->OnPreviousNPC.AddDynamic(this, &ADebugHUDController::OnPreviousNPC);
	}
}

void ADebugHUDController::OnEnableDebugMode(bool enable)
{
	if (mDebugHUDWidget->GetClass()->ImplementsInterface(UDebugHUD::StaticClass()))
	{
		IDebugHUD::Execute_OnEnableDebugMode(mDebugHUDWidget, enable);
	}
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnEnableDebugMode(mAgentDebugHUDWidget, enable);
	}
}

void ADebugHUDController::OnLogPredicate(const ANPCAIController* controller, const FString& predicate)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogPredicate(mAgentDebugHUDWidget, controller, predicate);
	}
}

void ADebugHUDController::OnLogClear()
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogClear(mAgentDebugHUDWidget);
	}
}

void ADebugHUDController::OnNextNPC(const ANPCAIController* controller)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnNextNPC(mAgentDebugHUDWidget, controller);
	}
}

void ADebugHUDController::OnPreviousNPC(const ANPCAIController* controller)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnPreviousNPC(mAgentDebugHUDWidget, controller);
	}
}