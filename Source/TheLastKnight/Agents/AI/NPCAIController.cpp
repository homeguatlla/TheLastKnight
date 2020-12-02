#include "NPCAIController.h"
#include <TheLastKnight/NAI/source/goap/IGoapPlanner.h>
#include <TheLastKnight/NAI/source/goap/goals/GoToGoal.h>
#include <TheLastKnight/NAI/source/goap/predicates/GoToPredicate.h>
#include <TheLastKnight/NAI/source/goap/planners/TreeGoapPlanner.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Agents/AgentBuilder.h>
#include <TheLastKnight/Agents/AI/NPCAgent.h>
#include <TheLastKnight/utils/UtilsLibrary.h>

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

FString ANPCAIController::GetAgentName_Implementation() const
{
	return GetCharacter()->GetName();
}

FString ANPCAIController::GetAgentCurrentState_Implementation() const
{
	return utils::UtilsLibrary::ConvertToFString(NAI::Goap::AgentStateMap[mAgent->GetCurrentState()]);
}

void ANPCAIController::CreateNavigationPlanner()
{
	mNavigationPlanner = std::make_shared<NavigationPlanner>(GetWorld());
}

void ANPCAIController::CreateAgent()
{
	AgentBuilder builder;

	const auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner);
	const auto predicate1 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "SheriffOffice");
	const auto predicate2 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "Saloon");
	auto gameMode = GetWorld()->GetAuthGameMode<ATheLastKnightGameMode>();
	
	if (gameMode->IsValidLowLevel())
	{
		auto eventDispatcher = gameMode->GetEventDispatcher();
		mAgent = builder.AddGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
						.AddController(this)
						.AddGoal(goToGoal)
						.AddPredicate(predicate1)
						.AddPredicate(predicate2)
						.AddEventDispatcher(eventDispatcher)
						.Build<NPCAgent>();

		mAgent->StartUp();
	}
}