// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"

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
}