// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Blueprint/UserWidget.h>
#include "MainHUD.generated.h"

/**
 * Basic Main HUD
 */
UCLASS()
class THELASTKNIGHT_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainHUD();

	void BeginPlay() override;

	UFUNCTION()
	void OnLogPredicate(const FString& predicate);

private:
	void BindToDelegate();

	//estod métodos probablemente sean estáticos en alguna libreria-
	template <class InterfaceTypeSource, class InterfaceTypeTarget = InterfaceTypeSource>
	InterfaceTypeTarget* CreateHUDFromClass(TSubclassOf<InterfaceTypeSource> hudClass, bool autoAddToViewport = true, int32 zOrder = 0)
	{
		InterfaceTypeTarget* widget = InstantiateHUD<InterfaceTypeSource, InterfaceTypeTarget>(hudClass, autoAddToViewport, zOrder);
		return widget;
	}

	template <class InterfaceTypeSource, class InterfaceTypeTarget>
	InterfaceTypeTarget* InstantiateHUD(TSubclassOf<UUserWidget> hudClass, bool autoAddToViewport, int32 zOrder)
	{
		//CreateWidget need different FName for each create otherwise it returns a pointer to the previously create with the same name.
			//refer to the link below
			//https://answers.unrealengine.com/questions/810228/strange-behaviour-of-uuserwidgetcreatewidgetinstan.html?sort=oldest

		mHudIndex++;
		FString name = hudClass->GetName() + "_" + FString::FromInt(mHudIndex) + "_" + this->GetName();
		UUserWidget* widget = CreateWidget<UUserWidget>(this->GetOwningPlayerController(), hudClass, FName(*name));

		if (autoAddToViewport)
			widget->AddToViewport(zOrder == 0 ? mHudIndex + 1 : zOrder);
		//widget->InitializeWidget();

		return Cast<InterfaceTypeTarget>(widget);
	}

public:
	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "CharacterHUD")
	TSubclassOf<UUserWidget> CharacterHUDWidgetClass;

	/** Blueprint class which displays the ability */
	UPROPERTY(EditAnywhere, Category = "Debug HUD")
	TSubclassOf<UUserWidget> DebugHUDWidgetClass;

	UPROPERTY()
	UUserWidget* mCharacterHUDWidget;

	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	//esto hay que arreglarlo
	int mHudIndex;
};
