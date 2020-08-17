#include "NPCAIController.h"
#include <TheLastKnight/Agents/AI/NPCAgent.h>
#include <TheLastKnight/NAI/source/goap/IGoapPlanner.h>
#include <TheLastKnight/NAI/source/goap/IGoal.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>
#include <TheLastKnight/NAI/source/goap/goals/GoToGoal.h>
#include <TheLastKnight/NAI/source/goap/predicates/GoToPredicate.h>
#include <TheLastKnight/Agents/AgentBuilder.h>
#include <TheLastKnight/NAI/source/goap/planners/TreeGoapPlanner.h>
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	
	CreateNavigationPlanner();
	CreateAgent();
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(mAgent != nullptr)
	{
		mAgent->Update(DeltaTime);
	}
}

FVector ANPCAIController::GetPosition() const
{
	ACharacter* character = GetCharacter();
	return character->GetActorLocation();
}

void ANPCAIController::MoveTo(float elapsedTime, const FVector& point)
{
	if(point != mLastPoint || mLastPoint == FVector::ZeroVector)
	{
		mLastPoint = point;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, point);
	}
}

void ANPCAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}

void ANPCAIController::CreateNavigationPlanner()
{
	mNavigationPlanner = std::make_shared<NavigationPlanner>(GetWorld());
}

void ANPCAIController::CreateAgent()
{
	AgentBuilder builder;

	auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner);
	auto predicate = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "SheriffOffice");

	mAgent = builder.AddGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
					.AddController(this)
					.AddGoal(goToGoal)
					.AddPredicate(predicate)
					.Build<NPCAgent>();

	mAgent->StartUp();
}