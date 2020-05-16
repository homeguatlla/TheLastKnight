
#include <TheLastKnight/Abilities/AbilitityBase.h>

namespace TLN
{
	AbilityBase::AbilityBase(int cost, float maxCastingTime, float maxCooldownTime) :
		mCastCost{cost},
		mMaxCastingTime{maxCastingTime},
		mCastingTime{ 0.0f },
		mMaxCooldownTime{maxCooldownTime},
		mCooldownTimer{ 0.0f }
	{
	}

	bool AbilityBase::CanCast(int availableMana) const
	{
		return availableMana >= mCastCost && IsReadyToCast();
	}

	void AbilityBase::Cast(const FVector& location)
	{
		mCastingTime = mMaxCastingTime;
		mCooldownTimer = mMaxCooldownTime + mMaxCastingTime;
		DoStartCasting(location);
	}

	int AbilityBase::GetCastCost()
	{
		return mCastCost;
	}

	void AbilityBase::Update(float deltaTime)
	{
		if (mCastingTime > 0.0f)
		{
			mCastingTime -= deltaTime;
			if (mCastingTime <= 0.0f)
			{
				DoCast();
			}
		}
		mCooldownTimer -= deltaTime;
	}

	bool AbilityBase::IsCasting() const
	{
		return mCastingTime > 0.0f;
	}

	bool AbilityBase::IsReadyToCast() const
	{
		return mCooldownTimer <= 0.0f;
	}
}