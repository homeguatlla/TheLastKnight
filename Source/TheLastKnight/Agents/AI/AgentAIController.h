// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "AgentAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELASTKNIGHT_API AAgentAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;

	private:
		UFUNCTION()
		ATargetPoint* GetRandomWayPoint();

		UFUNCTION()
		void GoToRandomWayPoint();

	private:
		UPROPERTY()
		TArray<AActor*> mWayPoints;
};
