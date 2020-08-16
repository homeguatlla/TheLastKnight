#include "NavigationPlanner.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <TheLastKnight/NAI/source/navigation/INavigationPlanner.h>
#include <sstream>

NavigationPlanner::NavigationPlanner(UWorld* world)
{
	UGameplayStatics::GetAllActorsOfClass(world, ATargetPoint::StaticClass(), mWayPoints);

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
	throw std::logic_error("The method or operation is not implemented.");
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
	throw std::logic_error("The method or operation is not implemented.");
}
