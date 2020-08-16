
#include "FollowPathAction.h"
#include <TheLastKnight/NAI/source/goap/agent/IAgent.h>
#include <TheLastKnight/NAI/source/navigation/INavigationPath.h>

namespace NAI
{
	namespace Goap
	{
		FollowPathAction::FollowPathAction(
			const std::vector<std::shared_ptr<IPredicate>>& preConditions,
			const std::vector<std::shared_ptr<IPredicate>>& postConditions,
			std::weak_ptr<IAgent> agent,
			std::shared_ptr<Navigation::INavigationPath> path ) :
			BaseAction(preConditions, postConditions, 0),
			mPath{ path },
			mAgent { agent },
			mCurrentPointIndex {1}
		{
			mHasAccomplished = false;
		}

		void FollowPathAction::Process(float elapsedTime)
		{
			if (auto agent = mAgent.lock())
			{
				auto hasReachedPoint = mPath->HasReachedPoint(mCurrentPointIndex, agent->GetPosition(), 0.1f);
				if (hasReachedPoint)
				{
					if(mPath->IsEndOfPath(mCurrentPointIndex))
					{
						mHasAccomplished = true;
					}
					else
					{
						mCurrentPointIndex++;
					}
				}
				else
				{
					agent->MoveTo(elapsedTime, mPath->GetPoint(mCurrentPointIndex));
				}
			}
		}
	}
}
