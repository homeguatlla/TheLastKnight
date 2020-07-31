#include "DirectGoapPlanner.h"
#include <TheLastKnight/NAI/source/goap/IGoal.h>
#include <TheLastKnight/NAI/source/goap/IAction.h>
#include <TheLastKnight/NAI/source/goap/IPredicate.h>
#include <TheLastKnight/NAI/source/goap/GoapUtils.h>

namespace NAI
{
	namespace Goap
	{
		std::shared_ptr<IGoal> DirectGoapPlanner::GetPlan(std::vector<std::shared_ptr<IGoal>>& inputGoals, std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const
		{
			if (!inputPredicates.empty() && !inputGoals.empty())
			{
				std::shared_ptr<IGoal> lessCostGoal = nullptr;

				for (auto&& goal : inputGoals)
				{
					if (lessCostGoal == nullptr || goal->GetCost() < lessCostGoal->GetCost())
					{
						if (goal->SatisfyActions(inputPredicates))
						{
							lessCostGoal = goal;
						}
					}
				}

				return lessCostGoal;
			}

			return nullptr;
		}

		std::vector<std::shared_ptr<IGoal>> DirectGoapPlanner::GetPlanToReach(
			std::vector<std::shared_ptr<IGoal>>& inputGoals,
			std::vector<std::shared_ptr<IPredicate>>& inputPredicates,
			std::vector<std::shared_ptr<IPredicate>>& desiredPredicates) const
		{
			std::vector<std::shared_ptr<IGoal>> bestResult;

			return bestResult;
		}
	}
}