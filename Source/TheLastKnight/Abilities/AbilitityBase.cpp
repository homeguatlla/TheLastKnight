
#include <TheLastKnight/Abilities/AbilitityBase.h>

namespace TLN
{
	AbilityBase::AbilityBase(int cost, float maxCooldownTime) :
		mCastCost{cost},
		mMaxCooldownTime{maxCooldownTime}
	{
	}

	bool AbilityBase::CanCast(int availableMana) const
	{
		return availableMana >= mCastCost && IsReadyToCast();
	}

	void AbilityBase::Cast(const FVector& location)
	{
		mCooldownTimer = mMaxCooldownTime;
		DoCast(location);
	}

	int AbilityBase::GetCastCost()
	{
		return mCastCost;
	}

	void AbilityBase::Update(float deltaTime)
	{
		mCooldownTimer -= deltaTime;
	}

	bool AbilityBase::IsReadyToCast() const
	{
		return mCooldownTimer <= 0.0f;
	}
}