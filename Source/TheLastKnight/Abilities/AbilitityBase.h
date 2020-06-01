#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/IAbility.h>


class AAbility;
class AEventDispatcher;

namespace TLN
{
	class AbilityBase : public IAbility
	{
		public:
			AbilityBase(AAbility* ability, int cost, float maxCastingTime, float maxCooldownTime);
			virtual ~AbilityBase() = default;

			bool CanCast(int availableMana) const override;
			void CastSpell(const FVector& location) override;
			int GetCastCost() override;
			void Update(float deltaTime) override;
			bool IsCasting() const override;
			bool IsReadyToCast() const override;
			AAbility* GetAbilityActor() const  override { return mAAbility; }

		protected:
			virtual void DoStartCasting(const FVector& location) = 0;
			virtual void DoCastSpell() = 0;

			AEventDispatcher* GetEventDispatcher() const;

		private:
			int mCastCost;
			float mMaxCastingTime;
			float mCastingTime;
			float mMaxCooldownTime;
			float mCooldownTimer;

		protected:
			AAbility* mAAbility;
	};
};