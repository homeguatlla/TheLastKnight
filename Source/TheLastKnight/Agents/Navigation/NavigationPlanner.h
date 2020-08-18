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
	struct Location
	{
		std::string name;
		AActor* wayPoint;
		
		Location() = default;
		Location(const std::string& locationName, AActor* locationWayPoint) : name { locationName }, wayPoint { locationWayPoint } {}
	};

public:
	NavigationPlanner(UWorld* world);
	~NavigationPlanner() = default;

	void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, std::function<void(std::shared_ptr<NAI::Navigation::INavigationPath>) > callback) const override;
	glm::vec3 GetLocationGivenAName(const std::string& locationName) const override;
	unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const override;

private:
	void FindLocations();
	void CalculateCostMatrix();
	std::string GetLocationNameGivenAWayPoint(AActor* wayPoint) const;
	Location FindLocationNearest(const glm::vec3& point) const;

private:
	std::vector<Location> mLocations;
	std::map<std::pair<std::string, std::string>, unsigned int> mCostMatrix;
	UWorld* mWorld;
};
