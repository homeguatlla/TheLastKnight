
#include <TheLastKnight/Abilities/AbilitityBase.h>

namespace TLN
{
	bool AbilityBase::CanCast(int availableMana) const
	{
		return true;
	}

	void AbilityBase::Cast(const FVector& location)
	{
		DoCast(location);
	}

	int AbilityBase::GetCastCost()
	{
		return mCastCost;
	}
}