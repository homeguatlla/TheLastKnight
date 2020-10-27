// Fill out your copyright notice in the Description page of Project Settings.


#include <TheLastKnight/HUD/MainHUD.h>

#include <TheLastKnight/utils/UtilsLibrary.h>
#include <TheLastKnight/TheLastKnightGameMode.h>

#include <TheLastKnight/Debug/HUD/DebugHUDController.h>
#include <TheLastKnight/Character/HUD/CharacterHUD.h>

#include <Kismet/GameplayStatics.h>

AMainHUD::AMainHUD() : mHudIndex{0}
{
	
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDebugHUD(DebugHUDWidgetClasses);
	CreateCharacterHUD(CharacterHUDWidgetClasses);
	
	BindToDelegate();
}

void AMainHUD::CreateDebugHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mDebugHUDController = GetWorld()->SpawnActor<ADebugHUDController>(
		ADebugHUDController::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);
	mDebugHUDController->Initialize(mHudIndex, GetOwningPlayerController(), widgetClasses);
}

void AMainHUD::CreateCharacterHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mCharacterHUD = GetWorld()->SpawnActor<ACharacterHUD>(
		ACharacterHUD::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);
	mCharacterHUD->Initialize(mHudIndex, GetOwningPlayerController(), widgetClasses);
}

void AMainHUD::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(GetOwningPawn()->GetWorld()));
	if (gameMode)
	{
		
	}
}