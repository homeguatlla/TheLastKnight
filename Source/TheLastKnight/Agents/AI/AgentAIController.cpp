#include "AgentAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <TheLastKnight/Agents/AI/NPCAgent.h>
#include <TheLastKnight/NAI/source/goap/IGoapPlanner.h>
#include <TheLastKnight/NAI/source/goap/IGoal.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>

void AAgentAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), mWayPoints);
	
	CreateAgent();

	GoToRandomWayPoint();
}

void AAgentAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mAgent->Update(DeltaTime);
}

void AAgentAIController::CreateAgent()
{
	std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner;
	std::vector<std::shared_ptr<NAI::Goap::IGoal>> goals;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> predicates;

	//TODO create the goapPlanner, goals and predicates.
	mAgent = std::make_shared<NPCAgent>(goapPlanner, goals, predicates);
}

ATargetPoint* AAgentAIController::GetRandomWayPoint()
{
	auto index = FMath::RandRange(0, mWayPoints.Num() - 1);
	return Cast<ATargetPoint>(mWayPoints[index]);
}

void AAgentAIController::GoToRandomWayPoint()
{
	float acceptanceRadius = 10;
	auto result = MoveToActor(GetRandomWayPoint(), acceptanceRadius);
}