#include "NavigationPlanner.h"
#include <TheLastKnight/NAI/source/navigation/INavigationPlanner.h>
#include <TheLastKnight/Agents/Navigation/NavigationPath.h>

#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"

#include <sstream>

NavigationPlanner::NavigationPlanner(UWorld* world) : mWorld(world)
{
	UGameplayStatics::GetAllActorsOfClass(mWorld, ATargetPoint::StaticClass(), mWayPoints);

	CreateLocations();
}

void NavigationPlanner::CreateLocations()
{
	for (auto wayPoint : mWayPoints)
	{
		auto location = wayPoint->GetActorLocation();
		FString locationName = wayPoint->GetName();
		int32 index;
		locationName.FindChar('_', index);
		std::string name = std::string(TCHAR_TO_UTF8(*locationName.Left(index)));
		mLocations.insert(std::make_pair(name, glm::vec3(location.X, location.Y, location.Z)));
	}
}

void NavigationPlanner::GetPathFromTo(
const glm::vec3& origin, 
const glm::vec3& destination, 
std::function<void(std::shared_ptr<NAI::Navigation::INavigationPath>) > callback) const
{
	auto currentNavigationSystem = UNavigationSystemV1::GetCurrent(mWorld);
	auto path = currentNavigationSystem->FindPathToLocationSynchronously(
		mWorld, 
		FVector(origin.x, origin.y, origin.z), 
		FVector(destination.x, destination.y, destination.z));

	if (path != NULL)
	{
		auto navigationPath = std::make_shared<NavigationPath>();
		for (auto i = 0; i < path->PathPoints.Num(); ++i)
		{
			//DrawDebugSphere(mWorld, path->PathPoints[i], 10.0f, 12, FColor(255, 0, 0));
			auto point = path->PathPoints[i];
			navigationPath->AddPoint(glm::vec3(point.X, point.Y, point.Z));
		}

		callback(navigationPath);
	}
}

glm::vec3 NavigationPlanner::GetLocationGivenAName(const std::string& locationName) const
{
	auto it = mLocations.find(locationName);
	if (it != mLocations.end())
	{
		return it->second;
	}
	else
	{	
		std::stringstream msg;
		msg << "Location <" << locationName << "> not found!";
		throw std::logic_error(msg.str());
	}
}

unsigned int NavigationPlanner::GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const
{
	//TODO given both points find the nearest locations and find the cost.
	return 0;
}