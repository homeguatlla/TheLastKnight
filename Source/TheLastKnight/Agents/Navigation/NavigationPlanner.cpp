#include "NavigationPlanner.h"
#include <TheLastKnight/NAI/source/navigation/INavigationPlanner.h>
#include <TheLastKnight/Agents/Navigation/NavigationPath.h>

#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"

#include <algorithm>
#include <sstream>

NavigationPlanner::NavigationPlanner(UWorld* world) : mWorld(world)
{
	FindLocations();
	CalculateCostMatrix();	
}

void NavigationPlanner::FindLocations()
{
	TArray<AActor*> wayPoints;
	UGameplayStatics::GetAllActorsOfClass(mWorld, ATargetPoint::StaticClass(), wayPoints);

	for (auto i = 0; i < wayPoints.Num(); ++i)
	{
		auto locationName = GetLocationNameGivenAWayPoint(wayPoints[i]);
		mLocations.push_back(Location(locationName, wayPoints[i]));
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
	auto it = std::find_if(mLocations.begin(), mLocations.end(), 
		[&locationName](const Location& location){
			return location.name == locationName;
		});

	if (it != mLocations.end())
	{
		FVector point = it->wayPoint->GetActorLocation();
		return glm::vec3(point.X, point.Y, point.Z);
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
	auto location1 = FindLocationNearest(origin);
	auto location2 = FindLocationNearest(destination);

	if (location1.name != location2.name)
	{
		auto key = std::pair<std::string, std::string>(location1.name, location2.name);
		auto it = mCostMatrix.find(key);
		if(it != mCostMatrix.end())
		{
			return it->second;
		}
		else 
		{
			return std::numeric_limits<unsigned int>::max();
		}
	}

	return 0;
}

std::string NavigationPlanner::GetLocationNameGivenAWayPoint(AActor* wayPoint) const
{
	FString locationName = wayPoint->GetName();
	int32 index;
	locationName.FindChar('_', index);
	return std::string(TCHAR_TO_UTF8(*locationName.Left(index)));
}

NavigationPlanner::Location NavigationPlanner::FindLocationNearest(const glm::vec3& point) const
{
	float minDistance = std::numeric_limits<float>::max();
	NavigationPlanner::Location nearestLocation;

	for (auto location : mLocations)
	{
		FVector locationPoint = location.wayPoint->GetActorLocation();
		auto distance = glm::distance(point, glm::vec3(locationPoint.X, locationPoint.Y, locationPoint.Z));
		if (distance < minDistance)
		{
			nearestLocation = location;
			minDistance = distance;
		}
	}

	return nearestLocation;
}

void NavigationPlanner::CalculateCostMatrix()
{
	auto currentNavigationSystem = UNavigationSystemV1::GetCurrent(mWorld);

	for (auto i = 0; i < mLocations.size() - 1; ++i)
	{
		for (auto j = i + 1; j < mLocations.size(); ++j)
		{
			auto path = currentNavigationSystem->FindPathToLocationSynchronously(
				mWorld,
				mLocations[i].wayPoint->GetActorLocation(),
				mLocations[j].wayPoint->GetActorLocation()
				);
			mCostMatrix.insert(std::make_pair(std::make_pair(mLocations[i].name, mLocations[j].name), path->GetPathCost()));
			mCostMatrix.insert(std::make_pair(std::make_pair(mLocations[j].name, mLocations[i].name), path->GetPathCost()));
		}
	}
}