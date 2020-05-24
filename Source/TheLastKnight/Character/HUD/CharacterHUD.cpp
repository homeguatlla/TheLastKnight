// Fill out your copyright notice in the Description page of Project Settings.


#include <TheLastKnight/Character/HUD/CharacterHUD.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Character/HUD/IHealthHUD.h>
#include <Kismet/GameplayStatics.h>


ACharacterHUD::ACharacterHUD()
{

}

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDWidgetClass != nullptr)
	{
		mHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		
		if (mHUDWidget)
		{
			mHUDWidget->AddToViewport();
		}	
	}

	BindToDelegate();
}

void ACharacterHUD::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(GetOwningPawn()->GetWorld()));
	if (gameMode)
	{
		gameMode->GetEventDispatcher()->OnUpdateHealth.AddDynamic(this, &ACharacterHUD::OnUpdateHealthReceived);
	}
}

void ACharacterHUD::OnUpdateHealthReceived(float health)
{
	//bool usesInterface = mHUDWidget->Implements<IInterfaceHUD>();
	if (mHUDWidget->GetClass()->ImplementsInterface(UHealthHUD::StaticClass()))
	{
		//auto interfaceHUD = Cast<IInterfaceHUD>(mHUDWidget);
		IHealthHUD::Execute_OnUpdateHealth(mHUDWidget, health);
		//interfaceHUD->Execute_OnUpdateHealth(mHUDWidget, health);
	}
}