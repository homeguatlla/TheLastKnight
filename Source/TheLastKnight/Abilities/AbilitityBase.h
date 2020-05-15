#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/IAbility.h>

namespace TLN
{
	class AbilityBase : public IAbility
	{
		int mCastCost;
		float mMaxCooldownTime;
		float mCooldownTimer;

		public:
			AbilityBase(int cost, float maxCooldownTime);
			~AbilityBase() = default;

			bool CanCast(int availableMana) const override;
			void Cast(const FVector& location) override;
			int GetCastCost() override;
			void Update(float deltaTime) override;
			bool IsReadyToCast() const override;

		protected:
			virtual void DoCast(const FVector& location) = 0;
	};
};