#include "NavigationPlanner.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <TheLastKnight/NAI/source/navigation/INavigationPlanner.h>

NavigationPlanner::NavigationPlanner(UWorld* world)
{
	UGameplayStatics::GetAllActorsOfClass(world, ATargetPoint::StaticClass(), mWayPoints);

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
	throw std::logic_error("The method or operation is not implemented.");
}

unsigned int NavigationPlanner::GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
