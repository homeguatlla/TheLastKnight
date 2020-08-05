#include "NPCAIController.h"
#include <TheLastKnight/Agents/AI/NPCAgent.h>
#include <TheLastKnight/NAI/source/goap/IGoapPlanner.h>
#include <TheLastKnight/NAI/source/goap/IGoal.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>
#include <TheLastKnight/Agents/AgentBuilder.h>
#include <TheLastKnight/NAI/source/goap/planners/TreeGoapPlanner.h>

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	
	CreateNavigationPlanner();
	CreateAgent();
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mAgent->Update(DeltaTime);
}

FVector ANPCAIController::GetPosition() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ANPCAIController::MoveTo(float elapsedTime, const FVector& point)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ANPCAIController::CreateNavigationPlanner()
{
	mNavigationPlanner = std::make_shared<NavigationPlanner>(GetWorld());
}

void ANPCAIController::CreateAgent()
{
	AgentBuilder builder;

	/*mAgent = builder.AddGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
					.AddController(std::shared_ptr<IAgentAIController>(this))
					.Build<NPCAgent>();*/
}