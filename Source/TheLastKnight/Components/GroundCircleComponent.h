// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <memory>
#include "Components/DecalComponent.h"
#include "GroundCircleComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTKNIGHT_API UGroundCircleComponent : public UDecalComponent
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;

	private:
		void BindToDelegate();
		UFUNCTION()
		void OnEnableDebugMode(bool enable);
		UFUNCTION()
		void OnNextNPC(const FString& name);
		UFUNCTION()
		void OnPreviousNPC(const FString& name);

		FString GetAgentName() const;

	private:
		FString mAgentName;
};
