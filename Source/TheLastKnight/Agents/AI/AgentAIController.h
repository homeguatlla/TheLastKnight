// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include <memory>
#include "AgentAIController.generated.h"

namespace NAI { namespace Goap { class IAgent; } }

UCLASS()
class THELASTKNIGHT_API AAgentAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;
		void Tick(float DeltaTime) override;

private:
		UFUNCTION()
		ATargetPoint* GetRandomWayPoint();

		UFUNCTION()
		void GoToRandomWayPoint();

		void CreateAgent();

	private:
		UPROPERTY()
		TArray<AActor*> mWayPoints;

		std::shared_ptr<NAI::Goap::IAgent> mAgent;
};
