#include <TheLastKnight/Abilities/HealthAbility.h>
#include <TheLastKnight/Abilities/BPHealthAbility.h>

namespace TLN
{
	HealthAbility::HealthAbility(ABPHealthAbility* ability) : mBPHealthAbility{ ability }
	{
	}

	void HealthAbility::DoCast(const FVector& location)
	{
		if (mBPHealthAbility->IsValidLowLevel())
		{
			mBPHealthAbility->OnCast(location);
		}
	}
}