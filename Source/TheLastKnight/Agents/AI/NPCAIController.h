// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <memory>
#include <TheLastKnight/Agents/AI/IAgentAIController.h>
#include <TheLastKnight/Agents/Navigation/NavigationPlanner.h>
#include "NPCAIController.generated.h"

namespace NAI { namespace Goap { class IAgent; } }

UCLASS()
class THELASTKNIGHT_API ANPCAIController : public AAIController, public IAgentAIController
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;
		void Tick(float DeltaTime) override;

		FVector GetPosition() const override;
		void MoveTo(float elapsedTime, const FVector& point) override;

private:
		void CreateAgent();
		void CreateNavigationPlanner();
	private:

		std::shared_ptr<NAI::Goap::IAgent> mAgent;
		std::shared_ptr<NavigationPlanner> mNavigationPlanner;
};
