#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/NAI/glm/glm.hpp>
#include <TheLastKnight/NAI/source/navigation/INavigationPlanner.h>
#include <memory>
#include <map>
#include <string>

namespace NAI {
	namespace Navigation
	{
		class INavigationPath;
	}
}

class NavigationPlanner : public NAI::Navigation::INavigationPlanner
{
public:
	NavigationPlanner(UWorld* world);
	~NavigationPlanner() = default;

	void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, std::function<void(std::shared_ptr<NAI::Navigation::INavigationPath>) > callback) const override;
	glm::vec3 GetLocationGivenAName(const std::string& locationName) const override;
	unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const override;

private:
	void CreateLocations();

private:
	UPROPERTY()
	TArray<AActor*> mWayPoints;
	std::map<std::string, glm::vec3> mLocations;
};
