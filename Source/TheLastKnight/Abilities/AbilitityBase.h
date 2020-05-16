#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/IAbility.h>

namespace TLN
{
	class AbilityBase : public IAbility
	{
		int mCastCost;
		float mMaxCastingTime;
		float mCastingTime;
		float mMaxCooldownTime;
		float mCooldownTimer;

		public:
			AbilityBase(int cost, float maxCastingTime, float maxCooldownTime);
			~AbilityBase() = default;

			bool CanCast(int availableMana) const override;
			void Cast(const FVector& location) override;
			int GetCastCost() override;
			void Update(float deltaTime) override;
			bool IsCasting() const override;
			bool IsReadyToCast() const override;

		protected:
			virtual void DoStartCasting(const FVector& location) = 0;
			virtual void DoCast() = 0;
	};
};