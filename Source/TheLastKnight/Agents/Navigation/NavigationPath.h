#pragma once
#include "CoreMinimal.h"
#include <NAI/include/glm/glm.hpp>
#include <NAI/include/navigation/INavigationPath.h>

class NavigationPath : public NAI::Navigation::INavigationPath
{
public:
	NavigationPath() = default;
	~NavigationPath() = default;

	void AddPoint(const glm::vec3& point);
	bool Empty() const override;
	bool HasReachedPoint(int index, const glm::vec3& position, float precision) const override;
	glm::vec3 GetPoint(int index) const override;
	bool IsEndOfPath(int index) const override;

private:
	std::vector<glm::vec3> mPoints;
};
