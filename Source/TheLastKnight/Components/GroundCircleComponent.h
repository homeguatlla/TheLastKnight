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
		void OnNextNPC(const ANPCAIController* controller);
		UFUNCTION()
		void OnPreviousNPC(const ANPCAIController* controller);

		FString GetAgentName() const;

	private:
		FString mAgentName;
};
