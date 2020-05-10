#pragma once
#include "CoreMinimal.h"

namespace TLN
{
	class IAbility
	{
		public:
			virtual bool CanCast(int availableMana) const = 0;
			virtual void Cast(const FVector& location) = 0;
			virtual int GetCastCost() = 0;
			void Empty() {};
	};
};