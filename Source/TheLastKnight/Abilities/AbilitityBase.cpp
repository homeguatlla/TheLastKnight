
#include <TheLastKnight/Abilities/AbilitityBase.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/EventDispatcher.h>

namespace TLN
{
	AbilityBase::AbilityBase(AAbility* ability, int cost, float maxCastingTime, float maxCooldownTime) :
		mCastCost{cost},
		mMaxCastingTime{maxCastingTime},
		mCastingTime{ 0.0f },
		mMaxCooldownTime{maxCooldownTime},
		mCooldownTimer{ 0.0f },
		mAAbility { ability }
	{
	}

	bool AbilityBase::CanCast(int availableMana) const
	{
		return availableMana >= mCastCost && IsReadyToCast();
	}

	void AbilityBase::CastSpell(const FVector& location)
	{
		mCastingTime = mMaxCastingTime;
		mCooldownTimer = mMaxCooldownTime + mMaxCastingTime;
		DoStartCasting(location);
		NotifyStartCasting();
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
				DoCastSpell();
				NotifyCast();
			}
		}
		else
		{
			NotifyCooldownTime(mCooldownTimer);
		}

		mCooldownTimer -= deltaTime;
		if (IsReadyToCast())
		{
			NotifyReadyToCast();
		}
	}

	bool AbilityBase::IsCasting() const
	{
		return mCastingTime > 0.0f;
	}

	bool AbilityBase::IsReadyToCast() const
	{
		return mCooldownTimer <= 0.0f;
	}

	void AbilityBase::NotifyStartCasting()
	{
		GetEventDispatcher()->OnNotifyStartCasting.Broadcast(mAAbility->GetName());
	}

	void AbilityBase::NotifyCast()
	{
		GetEventDispatcher()->OnNotifyCast.Broadcast(mAAbility->GetName());
	}

	void AbilityBase::NotifyCooldownTime(float time)
	{
		GetEventDispatcher()->OnNotifyCooldownTime.Broadcast(mAAbility->GetName(), time);
	}

	void AbilityBase::NotifyReadyToCast()
	{
		GetEventDispatcher()->OnNotifyReadyToCast.Broadcast(mAAbility->GetName());
	}

	AEventDispatcher* AbilityBase::GetEventDispatcher() const
	{
		auto gameMode = mAAbility->GetWorld()->GetAuthGameMode<ATheLastKnightGameMode>();
		if (gameMode->IsValidLowLevel())
		{
			return gameMode->GetEventDispatcher();
		}
		return nullptr;
	}
}