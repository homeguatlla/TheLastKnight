#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/IAbility.h>

namespace TLN
{
	class AbilityBase : public IAbility
	{
		int mCastCost;

		public:
			AbilityBase() = default;
			~AbilityBase() = default;

			bool CanCast(int availableMana) const override;
			void Cast(const FVector& location) override;
			int GetCastCost() override;

		protected:
			virtual void DoCast(const FVector& location) = 0;
	};
};